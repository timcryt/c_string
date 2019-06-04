#include <stdlib.h>
#include <string.h>

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

void string_from_cstr(string * dest, const char * src) {
    unsigned int l = strlen(src);
    
    if (dest->capacity < l) {
        string_free(dest);
        dest->data = malloc(l);
        dest->capacity = l;
    }
    
    memcpy(dest->data, src, l);
    dest->len = l;

}


