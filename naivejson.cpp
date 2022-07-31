#include <assert.h>
#include "naivejson.h"

//只有一个成员的struct，可以确保类型安全
//json字符串
typedef struct {
    const char* json;
} json_context;

// 在cpp中也可以这样写：
// struct json_context
// {
//     const char* json;
// };
// 是一样的

//去除前导空格
void jsonParseWhitespace(json_context* c) {
    const char* p = c->json;
    while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r') ++p;
    c->json = p;
}

int jsonParseNull(json_context* c, json_value* v) {
    assert(*c->json == 'n');
    ++c->json;
    if (c->json[0] != 'u' || c->json[1] != 'l' || c->json[2] != 'l') {
        return JSON_PARSE_INVALID_VALUE;
    }
    c->json += 3;
    v->type = JSON_NULL;
    return JSON_PARSE_OK;
}

int jsonParseTrue(json_context* c, json_value* v) {
    assert(*c->json == 't');
    ++c->json;
    if (c->json[0] != 'r' || c->json[1] != 'u' || c->json[2] != 'e') {
        return JSON_PARSE_INVALID_VALUE;
    }
    c->json += 3;
    v->type = JSON_TRUE;
    return JSON_PARSE_OK;
}

int jsonParseFalse(json_context* c, json_value* v) {
    assert(*c->json == 'f');
    ++c->json;
    if (c->json[0] != 'a' || c->json[1] != 'l' || c->json[2] != 's' || c->json[3] != 'e') {
        return JSON_PARSE_INVALID_VALUE;
    }
    c->json += 4;
    v->type = JSON_FALSE;
    return JSON_PARSE_OK;
}

// int jsonParseStr(json_context* c, json_value* v) {

// }

int jsonParseValue(json_context* c, json_value* v) {
    switch (*c->json) {
        case 'n': return jsonParseNull(c, v);
        case 't': return jsonParseTrue(c, v);
        case 'f': return jsonParseFalse(c, v);
        // case '"': return jsonParseStr(c, v);
        case '\0': return JSON_PARSE_EXPECT_VALUE;
        default: return JSON_PARSE_INVALID_VALUE;
    }
}

//将json字符串转换为json_value结构体，并将结构体指针赋予jv。
int jsonParse(json_value* jv, const char* json) {
    assert(jv != nullptr);
    json_context c;
    c.json = json;
    jv->type = JSON_NULL;
    jsonParseWhitespace(&c);
    return jsonParseValue(&c, jv);
}

//返回jv结构体的json类型
int jsonGetType(const json_value* jv) {
    assert(jv != nullptr);
    return jv->type;
}