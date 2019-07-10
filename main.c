#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "c_string.h"


string string_new() {
    string t = {NULL, 0, 0, false};
    return t;
}

void string_free(string * x) {
    x->len = 0; 
    if (x->data != NULL && x->owned) {
        free(x->data);
        x->owned = false;
    }
    x->data = NULL;
}

void string_set_capacity(string * x, unsigned int new_capacity) {
    unsigned int l = x->len;
    if (new_capacity < x->len) {
        l = new_capacity;
    }
    char * new_data = malloc(new_capacity);
    if (x->data != NULL) {
        memcpy(new_data, x->data, l);
        if (x->owned) {
            free(x->data);
        }
    }
    x->capacity = new_capacity;
    x->data = new_data;
    x->owned = true;

}

void string_own(string * str) {
    string_set_capacity(str, str->len);
}

void string_from_cstr(string * dest, char * src) {
    string_free(dest);
    *dest = slice_from_cstr(src);
}

string slice_from_cstr(char * src) {
    string t = {src, strlen(src), 0, false};
    return t;
}

void string_to_cstr(char ** dest, string * src) {
    string_push(src, 0);
    *dest = src->data;
    src->owned = false;
}

string string_copy(string str) {
    string t = {str.data, str.len, 0, false};
    return t;
}

void string_append(string * dest, string src) {
    if (src.len > 0) {
        if (!dest->owned || dest->capacity < dest->len + src.len) {
            string_set_capacity(dest, dest->len + src.len);
        }
        memcpy(dest->data + dest->len, src.data, src.len);
        dest->len += src.len;
    }
}

void string_push(string * dest, char c) {
    if (!dest->owned || dest->capacity <= dest->len) {
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
        string t = {NULL, 0, 0, false};
        return t;
    } else if (end > str.len) {
        string t = {str.data + start, str.len - start - 1, 0, false};
        return t;
    } else {
        string t = {str.data + start, end - start, 0, false};
        return t;
    }
}

void string_insert(string * dest, string src, unsigned int start) {
    if (src.len > 0) {
        if (start >= dest->len) {
            string_append(dest, src);
        } else {
            if (!dest->owned || dest->capacity < dest->len + src.len) {
                string_set_capacity(dest, dest->len + src.len);
            }
            for (int i = dest->len - 1; i > start; i--) {
                dest->data[i+src.len] = dest->data[i];
            }
            memcpy(dest->data + start + 1, src.data, src.len);
        }
    }
}

void string_trim_right(string * str) {
    while (str->len > 0 && str->data[str->len-1] == ' ') {
        str->len--;
    }
}

void string_trim_left(string * str) {
    unsigned int first_smb = 0;
    while (first_smb < str->len && str->data[first_smb] == ' ') {
        first_smb++;
    } 
    if (str->owned) {
        for (unsigned int i = first_smb; i < str->len; i++) {
            str->data[i-first_smb] = str->data[i];
        }
    } else {
        str->data += first_smb;
    }
    str->len -= first_smb;
}

void string_trim(string * str) {
    string_trim_right(str);
    string_trim_left(str);
}

int string_cmp(string a, string b) {
    int l = a.len;
    if (b.len < a.len) {
        l = b.len;
    }
    int f = memcmp(a.data, b.data, l);
    if (f == 0) {
        if (a.len < b.len) {
            return -1;
        } else if (a.len > b.len) {
            return 1;
        } else {
            return 0;
        }
    } else {
        if (f > 0) {
            return 1;
        } else {
            return -1;
        }
    }
}

inline int string_lt(string a, string b) {
    return string_cmp(a, b) == -1;
}

inline int string_eq(string a, string b) {
    return string_cmp(a, b) == 0;
}

inline int string_gt(string a, string b) {
    return string_cmp(a, b) == 1;
}

unsigned int string_find(string where, string what) {
    if (what.len > where.len) {
        return where.len;
    } else if (what.len == 0) {
        return 0;
    } else {
        for (unsigned int i = 0; i + what.len <= where.len; i++) {
            if (!memcmp(where.data + i, what.data, what.len)) {
                return i;
            }
        }
        return where.len;
    }
}

int string_contains(string where, string what) {
    return string_find(where, what) != where.len;
}

void string_replace(string * s, string from, string to) {
    int i = 0;
    string mai = *s;
    string new = string_new();
    while (i <= mai.len - from.len) {
        if (string_eq(string_slice(mai, i, i + from.len), from)) {
            string_append(&new, to);
            i += from.len;
        } else {
            string_push(&new, mai.data[i]);
            i++;
        }
    }
    string_append(&new, string_slice(mai, i, mai.len));
    string_free(s);
    *s = new;
}

void string_fprint(FILE * stream, string s) {
    for (int i = 0; i < s.len; i++) {
        fputc(s.data[i], stream);
    }
}

inline void string_fprintln(FILE * stream, string s) {
    string_fprint(stream, s);
    fputc('\n', stream);
    fflush(stream);
}

inline void string_print(string s) {
    string_fprint(stdout, s);
}

inline void string_println(string s) {
    string_fprintln(stdout, s);
}

void string_finput(FILE * stream, string * s) {
    char c;
    *s = string_new();
    while ((c = fgetc(stream)) != '\n') {
        string_push(s, c);
    }
}

inline void string_input(string * s) {
    string_finput(stdin, s);
}