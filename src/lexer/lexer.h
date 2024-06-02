#ifndef LEXER_H_
#define LEXER_H_

#include <stdlib.h>
#include <stdbool.h>

typedef enum {
    TOKEN_END = 0,
    TOKEN_GENERAL_NAME,
    TOKEN_TYPEDEF,
    TOKEN_TYPEDEF_NAME,
    TOKEN_STRUCT,
    TOKEN_STRUCT_NAME,
    TOKEN_INT_TYPE,
    TOKEN_SHORT_TYPE,
    TOKEN_LONG_TYPE,
    TOKEN_CHAR_TYPE,
    TOKEN_FLOAT_TYPE,
    TOKEN_DOUBLE_TYPE,
    TOKEN_VAR_NAME,
    TOKEN_OPEN_BRACKET,
    TOKEN_CLOSE_BRACKET,
    TOKEN_SEMICOLON,
    TOKEN_OPEN_PAREN,
    TOKEN_CLOSE_PAREN,
    TOKEN_OPEN_CURL,
    TOKEN_CLOSE_CURL,
    TOKEN_INVALID,
} token_kind;

typedef struct token {
    token_kind kind;
    const char* text;
    size_t text_size;
} token;

typedef struct lexer {
    const char *content;
    size_t content_size;
    size_t cursor;
} lexer;


// make_lexer function initializes the new lexer struct
lexer make_lexer(const char *content, size_t content_size);

// lexer_trim_left removes spaces until it reaches a character
// that is not a space.
void lexer_trim_left(lexer *l);

// lexer_next function returns the next token
token lexer_next(lexer *l);

// is_name_start returns true if the character is a valid start
// character for keywords and names in C.
bool is_name_start(char x);

// is_name_symbol returns true if the character is a valid character
// that can be included in the keywords or names in C.
bool is_name_symbol(char x);

// starts_with returns true if the next token starts with
// the given prefix.
bool starts_with(lexer *l, const char *prefix);

#endif //LEXER_H_
