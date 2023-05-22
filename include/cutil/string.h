#ifndef __STRING_H
#define __STRING_H

typedef struct {
    char *str;
    int length;
} string_t;

string_t *string_new(const char *str);

void string_append(string_t *s, const char *str);

void string_prepend(string_t *s, const char *str);

void string_destroy(string_t *s);

#endif /* __STRING_H */
