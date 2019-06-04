#ifndef __C_STRING

typedef struct {
    char * data;
    unsigned int len;
    unsigned int capacity;
} string;

string string_new();
void string_free(string * x);

#endif
