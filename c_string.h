#ifndef __C_STRING

#define __C_STRING

#include <stdbool.h>

typedef struct {
    char * data;
    unsigned int len;
    unsigned int capacity;
    bool owned;
} string;

/* Создаёт пустую строку */
string string_new();
/* Освобождает владеющую строку и обнуляет её */
void string_free(string * x);

/* Переводит строку в стиле C в строку string */
void string_from_cstr(string * dest, char * src);
/* Создаёт невладеющую строку, ссылающуюся на данную строку в стиле C */
string slice_from_cstr(char * src);
/* Переводит строку string в строку в стиле C */
void string_to_cstr(char ** dest, string * src);
/* "Копируюет" строку (реального копирования памяти не происходит) */
string string_copy(string str);

/* Добавляет одну строку в конец другой */
void string_append(string * dest, string src);
/* Добавляет символ в конец строки */
void string_push(string * dest, char c);

/* Получает символ из конца строки */
char string_pop(string * src);

/* Получает невладеющую стрезку строки */
string string_slice(string str, unsigned int start, unsigned int end);

/* Вставляет строку dest в строку src начиная с символа start */
void string_insert(string * dest, string src, unsigned int start);

/* Удаляет пробелы с левого края строки */
void string_trim_left(string * str);
/* Удаляет пробелы с правого края строки */
void string_trim_right(string * str);
/* Удаляет пробелы с краёв строки */
void string_trim(string * str);

/* Сравнивает строки */
int string_cmp(string a, string b);
/* Возвращает 1, если строка a меньше строки b */
bool string_lt(string a, string b);
/* Возвращает 1, если две строки равны */
bool string_eq(string a, string b);
/* Возвращает 1, если строка a больше строки b */
bool string_gt(string a, string b);

/* Находит первое вхождение строки what в строке where */
unsigned int string_find(string where, string what);
/* Возвращает 1, если строка where содержит строку what */
bool string_contains(string where, string what);

/* Заменяет все вхождения строки from на сторику to в строке s  */
void string_replace(string * s, string from, string to);

/* Выводит строку в файл */
void string_fprint(FILE * stream, string s);
/* Выводит строку и перевод строки в файл */
void string_fprintln(FILE * stream, string s);
/* Выводит строку на экран */
void string_print(string s);
/* Выводит строку с переводом строки на экран */
void string_println(string s);

/* Вводит строку из файла */
void string_finput(FILE * stream, string * s);
/* Вводит строку с экрана */
void string_input(string * s);

#endif