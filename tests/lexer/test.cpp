#include "CppUTest/TestHarness.h"
#include <CppUTest/UtestMacros.h>

extern "C" {
    #include "lexer.h"
}

TEST_GROUP(lexer_test_group) {

    void setup() {
        // init before each test
    }

    void teardown() {
        // teardown after each test
    }
};

TEST(lexer_test_group, test_make_lexer) {
    const char* content = "SOME CONTENT";
    lexer l = make_lexer(content, 13);
    LONGS_EQUAL(0, l.cursor);
    LONGS_EQUAL(13, l.content_size);
}

TEST(lexer_test_group, test_lexer_trim_left) {
    const char* content = "    CONTENT";
    lexer l = make_lexer(content, 12);
    LONGS_EQUAL(0, l.cursor);
    lexer_trim_left(&l);
    LONGS_EQUAL(4, l.cursor);
    STRNCMP_EQUAL("C", (const char*)(l.content + l.cursor), 1);
}

TEST(lexer_test_group, test_lexer_trim_left_empty) {
    const char* content = "    ";
    lexer l = make_lexer(content, 4);
    LONGS_EQUAL(0, l.cursor);
    lexer_trim_left(&l);
    LONGS_EQUAL(4, l.cursor);
}

TEST(lexer_test_group, test_lexer_starts_with) {
    const char* content = "typedef struct int sometext";
    lexer l = make_lexer(content, 28);
    LONGS_EQUAL(0, l.cursor);
    CHECK(true == starts_with(&l, "typedef"));
    CHECK(false == starts_with(&l, "notin"));
    l.cursor = 8;
    CHECK(true == starts_with(&l, "struct"));
}

TEST(lexer_test_group, test_lexer_next) {
    const char* content = "  typedef struct int sometext";
    lexer l = make_lexer(content, 30);

    token t = lexer_next(&l);
    STRNCMP_EQUAL("typedef", t.text, 7);
    LONGS_EQUAL(7, t.text_size);
    LONGS_EQUAL(TOKEN_TYPEDEF, t.kind);

    token t2 = lexer_next(&l);
    STRNCMP_EQUAL("struct", t2.text, 6);
    LONGS_EQUAL(6, t2.text_size);
    LONGS_EQUAL(TOKEN_STRUCT, t2.kind);

    token t3 = lexer_next(&l);
    STRNCMP_EQUAL("int", t3.text, 3);
    LONGS_EQUAL(3, t3.text_size);
    LONGS_EQUAL(TOKEN_INT_TYPE, t3.kind);

    token t4 = lexer_next(&l);
    STRNCMP_EQUAL("sometext", t4.text, 8);
    LONGS_EQUAL(8, t4.text_size);
    LONGS_EQUAL(TOKEN_GENERAL_NAME, t4.kind);

    token t5 = lexer_next(&l);
    LONGS_EQUAL(TOKEN_END, t5.kind);
}
