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

void test_pop() {
    string s = string_new();
    
    string_from_cstr(&s, "Some string!");
    char c = string_pop(&s);
    
    assert(c == '!');
    assert(!memcmp(s.data, "Some string", s.len));
    
    string_free(&s);
}

void test_slice() {
    string s = string_new();
    
    string_from_cstr(&s, "Some string!");
    
    string t;
    
    t = string_slice(s, 0, 100);
    assert(!memcmp(t.data, "Some string", t.len));
    
    t = string_slice(s, 0, 4);
    assert(!memcmp(t.data, "Some", t.len));
    
    t = string_slice(s, 10, 1);
    assert(t.data == NULL);
    
    t = string_slice(s, 100, 110);
    assert(t.data == NULL);
    
    t = string_slice(s, 2, 8);
    assert(!memcmp(t.data, "me str", t.len));
    
    string_free(&s);
}

int main() {
    test_constructs_destructors();
    test_append();
    test_push();
    test_pop();
    test_slice();
}
