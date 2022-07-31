#include <cstdio>
// #include <stdlib.h>
#include <string>
#include <iostream>
#include "naivejson.h"

static int main_ret = 0;
static int test_count = 0;
static int test_pass = 0;

//do while(0) 包裹语句，防止在if中使用时使得if语句意外终止，注意最后的while后面没有分号
#define EXPECT_EQ_BASE(equality, expect, actual, format) \
    do {\
        ++test_count;\
        if (equality)\
            ++test_pass;\
        else {\
            fprintf(stderr, "%s:%d: expect: " format " actual: " format "\n", __FILE__, __LINE__, expect, actual);\
            main_ret = 1;\
        }\
    } while(0)

#define EXPECT_EQ_INT(expect, actual) EXPECT_EQ_BASE((expect == actual), expect, actual, "%d")

static void testParseNull() {
    json_value v;
    v.type = JSON_TRUE;
    EXPECT_EQ_INT(JSON_PARSE_OK, jsonParse(&v, "null"));
    EXPECT_EQ_INT(JSON_NULL, jsonGetType(&v));
}

static void testParseTrue() {
    json_value v;
    v.type = JSON_TRUE;
    EXPECT_EQ_INT(JSON_PARSE_OK, jsonParse(&v, "true"));
    EXPECT_EQ_INT(JSON_TRUE, jsonGetType(&v));
}

static void testParseFalse() {
    json_value v;
    v.type = JSON_TRUE;
    EXPECT_EQ_INT(JSON_PARSE_OK, jsonParse(&v, "false"));
    EXPECT_EQ_INT(JSON_FALSE, jsonGetType(&v));
}

static void testParse() {
    testParseNull();
}

int main() {
    testParse();
    printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
    return main_ret;
}