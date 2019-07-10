#ifndef __C_STRING

#define __C_STRING

#include <stdbool.h>

typedef struct {
    char * data;
    unsigned int len;
    unsigned int capacity;
    bool owned;
} string;

string string_new();
void string_free(string * x);

void string_from_cstr(string * dest, char * src);
string slice_from_cstr(char * src);
void string_to_cstr(char ** dest, string * src);
string string_copy(string str);

void string_append(string * dest, string src);
void string_push(string * dest, char c);

char string_pop(string * src);

string string_slice(string str, unsigned int start, unsigned int end);

void string_insert(string * dest, string src, unsigned int start);

void string_trim_left(string * str);
void string_trim_right(string * str);
void string_trim(string * str);

int string_cmp(string a, string b);
int string_lt(string a, string b);
int string_eq(string a, string b);
int string_gt(string a, string b);

unsigned int string_find(string where, string what);
int string_contains(string where, string what);

void string_replace(string * s, string from, string to);

#endif