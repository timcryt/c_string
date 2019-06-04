#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "c_string.h"

void test_constructs_destructors() {
    string s = string_new();
    
    string_from_cstr(&s, "Hello World!");
    assert(s.len == 12);
    assert(s.capacity == 12);
    assert(!memcmp(s.data, "Hello World!", s.len));
    
    char * t;
    string_to_cstr(&t, s);
    assert(strlen(t) == 12);
    assert(!strcmp(t, "Hello World!"));
    free(t);
    
    string_from_cstr(&s, "Some string");
    assert(s.len == 11);
    assert(s.capacity == 12);
    assert(!memcmp(s.data, "Some string", s.len));
    
    string_free(&s);
}

int main() {
    test_constructs_destructors();
}
