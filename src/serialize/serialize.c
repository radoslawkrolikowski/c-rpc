#include "serialize.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define BUFFER_SIZE 64

buffer_type* make_buffer(void) {
    buffer_type *bufTypePtr = malloc(sizeof(buffer_type));
    if (bufTypePtr == NULL)
        logger("[ERROR]", "allocate memory error", true);

    unsigned char *bufPtr = malloc(sizeof(unsigned char) * BUFFER_SIZE);
    if (bufPtr == NULL)
        logger("[ERROR]", "allocate memory error", true);

    bufTypePtr->buf = bufPtr;
    bufTypePtr->next = 0;
    bufTypePtr->size = BUFFER_SIZE;

    return bufTypePtr;
}

void delete_buffer(buffer_type *buf) {
    if (buf == NULL)
        logger("[ERROR]", "NULL pointer", true);

    if (buf->buf != NULL)
        free(buf->buf);

    free(buf);
}

void buf_write(buffer_type *buf, unsigned char *b, size_t n) {
    if (buf == NULL || buf->buf == NULL)
        logger("[ERROR]", "NULL pointer", true);

    if (buf->size <= (size_t)buf->next + n) {
        size_t scale_factor = 1;
        size_t available_space = buf->size - (size_t)buf->next;

        while (available_space < n) {
            scale_factor *= 2;
            available_space = (buf->size * scale_factor) - (size_t)buf->next;
        }

        unsigned char *newBufPtr = realloc(buf->buf, buf->size * scale_factor);
        if (newBufPtr == NULL)
            logger("[ERROR]", "allocate memory error", true);

        buf->buf = newBufPtr;
        buf->size = buf->size * scale_factor;
    }

    memcpy(buf->buf + (size_t)buf->next, b, n);
    buf->next += (unsigned int)n;
}

int buf_read(buffer_type *buf, unsigned char *dest, size_t n) {
    if ((size_t)buf->next + n >= buf->size)
        return 1;

    memcpy(dest, buf->buf + (size_t)buf->next, n);
    buf->next += (unsigned int)n;
    return 0;
}

int set_next(buffer_type *buf, unsigned int next) {
    if (next > buf->size)
        return 1;

    buf->next = next;
    return 0;
}

int buf_skip(buffer_type *buf, int skip_size) {
    unsigned int new_next;

    if (skip_size >= 0)
        new_next = buf->next + (unsigned int)skip_size;
    else
        new_next = buf->next - (unsigned int)abs(skip_size);

    if (new_next > buf->size)
        return 1;

    buf->next = new_next;

    return 0;
}

void logger(const char *tag, const char *message, bool _exit) {
    time_t now = time(0);
    char buff[50];
    strftime(buff, 50, "%Y-%m-%d %H:%M:%S", localtime(&now));
    fprintf(stderr, "%s [%s] %s\n", buff, tag, message);
    if (_exit)
        exit(1);
}
