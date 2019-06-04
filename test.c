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

void test_append() {
    string s = string_new();
    string_from_cstr(&s, "Some string");
    
    string t = string_new();
    string_from_cstr(&t, " with some information");
    
    string_append(&s, t);
    
    assert(!memcmp(s.data, "Some string with some information", s.len));
    
    string_free(&t);
    string_append(&s, t);
    assert(!memcmp(s.data, "Some string with some information", s.len));
    
    string_from_cstr(&t, "");
    string_append(&s, t);
    assert(!memcmp(s.data, "Some string with some information", s.len));    
    
    string_free(&s);
    string_free(&t);
}

void test_push() {
    string s = string_new();
    
    string_push(&s, 'A');
    assert(!memcmp(s.data, "A", 1));
    
    string_from_cstr(&s, "Hello");
    string_push(&s, ' ');
    
    string t = string_new();
    string_from_cstr(&t, "World!");
    
    string_append(&s, t);
    
    assert(!memcmp(s.data, "Hello World!", s.len));
    
    string_free(&s);
    string_free(&t);
}

int main() {
    test_constructs_destructors();
    test_append();
    test_push();
}
