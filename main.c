#include <stdlib.h>
#include <string.h>

#include "c_string.h"


string string_new() {
    string t = {NULL, 0, 0};
    return t;
}

void string_free(string * x) {
    x->len = 0;
    if (x->data != NULL && x->capacity != 0) {
        free(x->data);
        x->data = NULL;
        x->capacity = 0;
    }
}

void string_set_capacity(string * x, unsigned int new_capacity) {
    unsigned int l = x->len;
    if (new_capacity < x->len) {
        l = new_capacity;
    }
    
    char * new_data = malloc(new_capacity);
    if (x->data != NULL) {
        memcpy(new_data, x->data, l);
        if (x->data != 0) {
            free(x->data);
        }
    }
    
    x->data = new_data;
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

void string_to_cstr(char ** dest, string src) {
    *dest = malloc(src.len + 1);
    memcpy(*dest, src.data, src.len);
    (*dest)[src.len] = 0;
}

void string_append(string * dest, string src) {
    if (dest->capacity < dest->len + src.len) {
        string_set_capacity(dest, dest->len + src.len);
    }
    memcpy(dest->data + dest->len, src.data, src.len);
    dest->len += src.len;
}

void string_push(string * dest, char c) {
    if (dest->capacity <= dest->len) {
        string_set_capacity(dest, dest->len * 2 + 1);
    }
    dest->data[dest->len] = c;
    dest->len++;
}

char string_pop(string * src) {
    if (src->len != 0) {
        src->len--;
        return src->data[src->len];
    }
    return 0;
}

string string_slice(string str, unsigned int start, unsigned int end) {
    if (end < start || start >= str.len || str.data == NULL) {
        string t = {NULL, 0, 0};
        return t;
    } else if (end > str.len) {
        string t = {str.data + start, str.len - start - 1, 0};
        return t;
    } else {
        string t = {str.data + start, end - start, 0};
        return t;
    }
}
