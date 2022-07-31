//使用inline来替代宏，会使format变得麻烦，同时也造成__FILE__和__LINE__宏不能正常使用，
//这两个编译器宏只有在被替换到最终的代码位置时才能正确发挥作用，而宏展开在预编译期，inline展开在编译期，此时__LINE__已经展开为inline函数中的行号了。


#include <cstdio>
// #include <stdlib.h>
#include <string>
#include <iostream>
#include "tinyjson.h"

static int main_ret = 0;
static int test_count = 0;
static int test_pass = 0;

inline void expectEqualBase(bool equality, int expect, int actual) {
    ++test_count;
    if (equality) {
        ++test_pass;
    } else {
        // fprintf(stderr, "%s:%d:expect:" + format + " actual:"+ format + " \n", __FILE__, __LINE__, expect, actual);
        std::cerr << __FILE__ << ":" << __LINE__ << ": expect: " << expect << " actual:" << actual << std::endl;
        main_ret = 1;
    }
}

inline void expectEqualInt(int expect, int actual) {
    expectEqualBase((expect == actual), expect, actual);
}


static void testParseNull() {
    json_value v;
    v.type = JSON_TRUE;
    expectEqualInt(JSON_PARSE_OK, jsonParse(&v, "null"));
    expectEqualInt(JSON_NULL, jsonGetType(&v));
}

static void testParseTrue() {

}

static void testParseFalse() {
    
}

static void testParse() {
    testParseNull();
}

int main() {
    testParse();
    printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
    return main_ret;
}