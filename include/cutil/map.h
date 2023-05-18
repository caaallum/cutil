#ifndef __MAP_H
#define __MAP_H

typedef struct map_t map_t;

/**********************************************************
 * \brief Init new map
 *
 * \param type Key type of map
 *
 * \returns newly created map
 **********************************************************/
map_t *map_new(void);

/**********************************************************
 * \brief Free map memory
 *
 * \param map this
 **********************************************************/
void map_destroy(map_t *map);

/**********************************************************
 * \brief Get total of items in map
 *
 * \param map this
 *
 * \returns int total
 **********************************************************/
int map_total(const map_t *map);

/**********************************************************
 * \brief Add item to map
 *
 * \param map this
 * \param key map key
 * \param val map value
 **********************************************************/
void _map_add_key_char(map_t *const map, char key, void *val);
void _map_add_key_string(map_t *const map, const char *key, void *val);
void _map_add_key_int(map_t *const map, int key, void *val);
#define map_add(map, key, val)                                                 \
  _Generic((key),                                                              \
      char: _map_add_key_char,                                                 \
      char *: _map_add_key_string,                                             \
      const char *: _map_add_key_string,                                       \
      int: _map_add_key_int)(map, key, val)

/**********************************************************
 * \brief Add item to map and copy value
 *
 * \param map  this
 * \param key  map key
 * \param val  map value
 * \param size size size of value
 **********************************************************/
void _map_pushback_key_char(map_t *const map, char key, void *val, int size);
void _map_pushback_key_string(map_t *const map, const char *const key,
                              void *val, int size);
void _map_pushback_key_int(map_t *const map, int key, void *val, int size);
#define map_pushback(map, key, val, size)                                      \
  _Generic((key),                                                              \
      char: _map_pushback_key_char,                                            \
      char *: _map_pushback_key_string,                                        \
      const char *: _map_pushback_key_string,                                  \
      int: _map_pushback_key_int)(map, key, val, size)

/**********************************************************
 * \brief Get item from map
 *
 * \param map this
 * \param key map key
 *
 * \returns item if valid key, NULL if not
 **********************************************************/
void *_map_get_key_char(map_t *const map, char key);
void *_map_get_key_string(map_t *const map, const char *const key);
void *_map_get_key_int(map_t *const map, int key);
#define map_get(map, key)                                                      \
  _Generic((key),                                                              \
      char: _map_get_key_char,                                                 \
      char *: _map_get_key_string,                                             \
      const char *: _map_get_key_string,                                       \
      int: _map_get_key_int)(map, key)

#define map_get_int(map, key) (*((int *)map_get(map, key)))
#define map_get_string(map, key) ((char *)map_get(map, key))
#define map_get_struct(type, map, key) ((type *)map_get(map, key))
#endif /* __MAP_H */
