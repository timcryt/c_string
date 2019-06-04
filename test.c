#include "c_string.h"

void test_constructs_destructors() {
    string s = string_new();
    string_free(&s);
}

int main() {
    test_constructs_destructors();
}
