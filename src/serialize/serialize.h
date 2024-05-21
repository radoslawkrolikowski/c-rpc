#ifndef SERIALIZE_H
#define SERIALIZE_H

#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

typedef struct buffer_type {
    unsigned char *buf;
    size_t size;
    unsigned int next;
} buffer_type;

// make_buffer function allocates the memory for the buffer_type struct
// and underlying buffer array.
buffer_type* make_buffer(void);

// delete_buffer function deallocates the memory for the buffer_type struct
// and underlying buffer array.
void delete_buffer(buffer_type *buf);

// buf_write function writes 'n' bytes of data from 'b'
// into the buffer array and forwards the 'next' index.
void buf_write(buffer_type *buf, unsigned char *b, size_t n);

// buf_read function copies 'n' bytes from buffer array into
// the 'dest' memory address and forwards the 'next' index.
// returns 1 if read failed, otherwise it returns 0.
int buf_read(buffer_type *buf, unsigned char *dest, size_t n);

// set_next function sets the value of the next index in the buffer.
// use case: set 'next' to 0 when writting is finished.
// returns 1 if the 'next' value is greater than buffer size,
// otherwise it returns 0;
int set_next(buffer_type *buf, unsigned int next);

// logger is a helper function for displaying error messages and exiting
// the program.
void logger(const char *tag, const char *message, bool _exit);

#endif // SERIALIZE_H
