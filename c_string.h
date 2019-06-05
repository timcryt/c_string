#ifndef __C_STRING

#define __C_STRING

typedef struct {
    char * data;
    unsigned int len;
    unsigned int capacity;
} string;

string string_new();
void string_free(string * x);

void string_from_cstr(string * dest, const char * src);
void string_to_cstr(char ** dest, string src);

void string_append(string * dest, string src);
void string_push(string * dest, char c);

char string_pop(string * src);

string string_slice(string str, unsigned int start, unsigned int end);

void string_insert(string * dest, string src, unsigned int start);

void string_trim_left(string * str);
void string_trim_right(string * str);
void string_trim(string * str);

#endif
