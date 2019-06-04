#include <stdlib.h>

#include "c_string.h"


string string_new() {
    string t = {NULL, 0, 0};
    return t;
}

void string_free(string * x) {
    x->len = 0;
    if (x->data != NULL) {
        free(x->data);
        x->data = NULL;
        x->capacity = 0;
    }
}


