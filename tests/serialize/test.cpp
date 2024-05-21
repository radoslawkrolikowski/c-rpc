#include "CppUTest/TestHarness.h"
#include <CppUTest/UtestMacros.h>
#include <stdio.h>

extern "C" {
    #include "serialize.h"
    #include <stdlib.h>
    #include <string.h>
}

TEST_GROUP(serialize_test_group) {

    void setup() {
        // init before each test
    }

    void teardown() {
        // teardown after each test
    }
};

TEST(serialize_test_group, test_make_buffer) {
    buffer_type *buf = make_buffer();
    LONGS_EQUAL(0, buf->next);
    CHECK(buf->size > 0);
    delete_buffer(buf);
}

TEST(serialize_test_group, test_buf_write) {
    buffer_type *buf = make_buffer();
    unsigned char *b = (unsigned char*)malloc(sizeof(unsigned char) * 8);
    if (b == NULL)
        FAIL("allocate memory error");

    strncpy((char*)b, "ABCDEFG", 8);
    buf_write(buf, b, 7);
    LONGS_EQUAL(7, buf->next);
    STRNCMP_EQUAL((const char*)b, (const char*)buf->buf, 7);

    delete_buffer(buf);
    free(b);
}

TEST(serialize_test_group, test_buf_write_many) {
    buffer_type *buf = make_buffer();
    unsigned char *b = (unsigned char*)malloc(sizeof(unsigned char) * 300);
    if (b == NULL)
        FAIL("allocate memory error");

    int pos[6] = {0, 20, 50, 100, 200, 300};

    for (int i = 1; i <= 5 ; i++) {
        int n = pos[i] - pos[i-1];

        memset(b + pos[i-1], 'A' + i, (size_t)n);

        buf_write(buf, b + pos[i-1], (size_t)n);

        LONGS_EQUAL(pos[i], buf->next);
        STRNCMP_EQUAL(
                (const char*)b + pos[i-1],
                (const char*)buf->buf + pos[i-1],
                (size_t)n
        );
    }

    LONGS_EQUAL(512, buf->size);

    delete_buffer(buf);
    free(b);
}

TEST(serialize_test_group, test_set_next) {
    buffer_type *buf = make_buffer();
    LONGS_EQUAL(0, buf->next);
    LONGS_EQUAL(1, set_next(buf, 1000));
    LONGS_EQUAL(0, set_next(buf, 25));
    LONGS_EQUAL(25, buf->next);
    delete_buffer(buf);
}
