#ifndef __STRING_H
#define __STRING_H

typedef struct {
    char *str;
    int length;
} string_t;

/**********************************************************
 * \brief Init new string
 *
 * \param str string to init from
 *
 * \returns newly created string
 **********************************************************/
string_t *string_new(const char *str);

/**********************************************************
 * \brief Append string to string struct
 *
 * \param s     string_t struct 
 * \param str   string to append
 **********************************************************/
void string_append(string_t *s, const char *str);

/**********************************************************
 * \brief Prepend string to string struct
 *
 * \param s     string_t struct
 * \param str   string to prepend
 **********************************************************/
void string_prepend(string_t *s, const char *str);

/**********************************************************
 * \brief Destroy string struct
 *
 * \param s     string_t to destroy
 **********************************************************/
void string_destroy(string_t *s);

#endif /* __STRING_H */
