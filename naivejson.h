#pragma once //只能保证物理上的同一个文件不会被包含多次，对于同内容文件的拷贝不起作用。由编译器提供，不受C/C++标准保护
// #ifndef TINYJSON_H__
// #define TINYJSON_H__
//受到标准保护，但是无法解决宏名碰撞问题，且解析更慢。

typedef enum {JSON_NULL, JSON_FALSE, JSON_TRUE, JSON_NUM, JSON_STR, jSON_ARRAY, JSON_OBJ} json_type;
//json结构体
typedef struct {
    json_type type;
    double num;
} json_value;

enum {
    JSON_PARSE_OK = 0,
    JSON_PARSE_EXPECT_VALUE,
    JSON_PARSE_INVALID_VALUE,
    JSON_PARSE_ROOT_NOT_SINGULAR
};

int jsonParse(json_value* jv, const char* json);
int jsonGetType(const json_value* jv);
double jsonGetNum(const json_value* jv);
int jsonGenerate(const json_value* jv, char* json);

// #endif