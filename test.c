#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "c_string.h"

void test_constructs_destructors() {
    string s = string_new();
    
    string_from_cstr(&s, "Hello World!");
    assert(s.len == 12);
    assert(!memcmp(s.data, "Hello World!", s.len));
    
    char * t;
    string_to_cstr(&t, &s);
    assert(strlen(t) == 12);
    assert(!strcmp(t, "Hello World!"));
    free(t);
    
    string_from_cstr(&s, "Some string");
    assert(s.len == 11);
    assert(!memcmp(s.data, "Some string", s.len));

    string u = string_copy(s);

    assert(!memcmp(u.data, "Some string", u.len));
    
    string_free(&s);
}

void test_append() {
    string s = string_new();
    string_from_cstr(&s, "Some string");
    
    
    string_append(&s, slice_from_cstr(" with some information"));
    
    assert(!memcmp(s.data, "Some string with some information", s.len));
    
    string t = string_new();
    string_free(&t);
    string_append(&s, t);
    assert(!memcmp(s.data, "Some string with some information", s.len));
    
    string_append(&s, slice_from_cstr(""));
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
    
    string_append(&s, slice_from_cstr("World!"));
    
    assert(!memcmp(s.data, "Hello World!", s.len));
    
    string_free(&s);
}

void test_pop() {
    string s = slice_from_cstr("Some string!");
    
    char c = string_pop(&s);
    
    assert(c == '!');
    assert(!memcmp(s.data, "Some string", s.len));
    
    string_free(&s);
}

void test_slice() {
    string s = slice_from_cstr("Some string!");
    
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

void test_insert() {
    string s = slice_from_cstr("HellWorld!");

    string_insert(&s, slice_from_cstr("o "), 3);
    
    assert(!memcmp(s.data, "Hello World!", s.len));
    
    string_free(&s);
}

void test_trim() {
    string s = slice_from_cstr("    ");

    string_trim_left(&s);
    assert(s.len == 0);

    string_from_cstr(&s, "    ");

    string_trim_right(&s);
    assert(s.len == 0);

    string_from_cstr(&s, "    Hello World!");
    string_trim(&s);
    assert(!memcmp(s.data, "Hello World!", s.len));

    string_from_cstr(&s, "  Hello World!  ");
    string_trim(&s);
    assert(!memcmp(s.data, "Hello World!", s.len));

    string_from_cstr(&s, "Hello World!    ");
    string_trim(&s);
    assert(!memcmp(s.data, "Hello World!", s.len));

    string_free(&s);
}

void test_cmp() {
    string s = slice_from_cstr("HELLO WORLD");

    assert(string_lt(string_slice(s, 0, s.len - 1), s));
    assert(string_gt(s, string_slice(s, 1, s.len)));
    assert(string_eq(string_slice(s, 0, 0), string_slice(s, 0, 0)));
    assert(string_eq(string_slice(s, 2, 3), string_slice(s, 3, 4)));

    string_free(&s);
}

void test_find() {
    string s = slice_from_cstr("Hello, World!");

    assert(string_find(s, slice_from_cstr("ll")) == 2);

    assert(string_find(s, slice_from_cstr("o")) == 4);

    assert(string_find(s, slice_from_cstr("A")) == s.len);

    string_free(&s);
}

int main() {
    test_constructs_destructors();
    test_append();
    test_push();
    test_pop();
    test_slice();
    test_insert();
    test_trim();
    test_cmp();
    test_find();
}
