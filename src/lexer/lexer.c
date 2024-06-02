#include "lexer.h"
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

token general_tokens[] = {
    {.text = ";", .kind = TOKEN_SEMICOLON, .text_size = 1},
    {.text = "(", .kind = TOKEN_OPEN_PAREN, .text_size = 1},
    {.text = "(", .kind = TOKEN_OPEN_PAREN, .text_size = 1},
    {.text = ")", .kind = TOKEN_CLOSE_PAREN, .text_size = 1},
    {.text = "{", .kind = TOKEN_OPEN_CURL, .text_size = 1},
    {.text = "}", .kind = TOKEN_CLOSE_CURL, .text_size = 1},
    {.text = "]", .kind = TOKEN_CLOSE_BRACKET, .text_size = 1},
    {.text = "[", .kind = TOKEN_OPEN_BRACKET, .text_size = 1},
};

token symbol_tokens[] = {
    {.text = "typedef", .kind = TOKEN_TYPEDEF, .text_size = 7},
    {.text = "struct", .kind = TOKEN_STRUCT, .text_size = 6},
    {.text = "int", .kind = TOKEN_INT_TYPE, .text_size = 3},
    {.text = "short", .kind = TOKEN_SHORT_TYPE, .text_size = 5},
    {.text = "long", .kind = TOKEN_LONG_TYPE, .text_size = 4},
    {.text = "char", .kind = TOKEN_CHAR_TYPE, .text_size = 4},
    {.text = "float", .kind = TOKEN_FLOAT_TYPE, .text_size = 5},
    {.text = "double", .kind = TOKEN_DOUBLE_TYPE, .text_size = 6},
};

#define GENERAL_TOKENS_LEN (sizeof(general_tokens)/sizeof(general_tokens[0]))
#define SYMBOL_TOKENS_LEN (sizeof(symbol_tokens)/sizeof(symbol_tokens[0]))

lexer make_lexer(const char *content, size_t content_size) {
    lexer l = {0};
    l.content = content;
    l.content_size = content_size;
    return l;
}

void lexer_trim_left(lexer *l) {
    while (l->cursor < l->content_size && isspace(*(l->content + l->cursor))) {
        l->cursor++;
    }
}

bool starts_with(lexer *l, const char *prefix) {
    if ((l->content_size - l->cursor) < strlen(prefix))
        return false;

    for (size_t i = 0; i < strlen(prefix); i++) {
        if (*(l->content + l->cursor + i) != prefix[i])
            return false;
    }

    return true;
}

token lexer_next(lexer *l) {
    token t = {
        .text = l->content + l->cursor,
        .text_size = 0,
    };

    lexer_trim_left(l);

    if (l->cursor >= l->content_size)
        return t;

    for (int i = 0; i < (int)GENERAL_TOKENS_LEN; i++) {
        if (starts_with(l, general_tokens[i].text)) {
            l->cursor += strlen(general_tokens[i].text);
            return general_tokens[i];
        }
    }

    if (l->cursor >= l->content_size)
        return t;

    if (is_name_start(*(l->content + l->cursor))) {
        t.text = l->content + l->cursor;
        while (l->cursor < l->content_size
                && is_name_symbol(*(l->content + l->cursor))) {
            l->cursor++;
            t.text_size++;
        }

        for (int i = 0; i < (int)SYMBOL_TOKENS_LEN; i++) {
            if (symbol_tokens[i].text_size == t.text_size) {
                if (strncmp(symbol_tokens[i].text, t.text, t.text_size) == 0) {
                    return symbol_tokens[i];
                }
            }
        }

        t.kind = TOKEN_GENERAL_NAME;
        return t;
    }

    l->cursor++;

    if (l->cursor >= l->content_size)
        return t;

    t.kind = TOKEN_INVALID;
    t.text_size = 1;

    return t;
}

bool is_name_start(char x) {
    return isalpha(x) || x == '_';
}

bool is_name_symbol(char x) {
    return isalnum(x) || x == '_';
}
