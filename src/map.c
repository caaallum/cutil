#include <cutil/map.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAP_INIT_CAPACITY 4

typedef struct {
  enum { TYPE_CHAR, TYPE_STRING, TYPE_INT } type;

  union {
    char c;
    char *s;
    int i;
  } key;
  void *val;
  bool alloced;
} map_val_t;

struct map_t {
  map_val_t **map;
  int total;
  int capacity;
};

map_t *map_new(void) {
  map_t *map = malloc(sizeof(map_t));
  assert(map);

  map->capacity = MAP_INIT_CAPACITY;
  map->total = 0;
  map->map = malloc(sizeof(map_val_t *) * map->capacity);
  assert(map->map);

  return map;
}

map_val_t *map_val_new(void) {
  map_val_t *map_val = malloc(sizeof(map_val_t));
  assert(map_val);

  map_val->alloced = false;

  return map_val;
}

void map_destroy(map_t *map) {
  for (int i = 0; i < map->total; i++) {
    map_val_t *val = map->map[i];
    if (val->type == TYPE_STRING) {
      free(val->key.s);
    }
    if (val->alloced) {
      free(val->val);
    }
    free(val);
  }
  free(map->map);
  free(map);
}

int map_total(const map_t *map) {
  assert(map);
  return map->total;
}

void _map_resize(map_t *const map) {
  if (map->total != map->capacity) {
    return;
  }

  int capacity = map->capacity * 2;

  map_val_t **items = realloc(map->map, sizeof(map_val_t *) * capacity);
  assert(items);

  map->map = items;
  map->capacity = capacity;
}

void _map_add_key_char(map_t *const map, char key, void *val) {
  assert(map);
  map_val_t *map_val = map_val_new();

  map_val->key.c = key;
  map_val->type = TYPE_CHAR;
  map_val->val = val;

  _map_resize(map);

  map->map[map->total++] = map_val;
}

void _map_add_key_string(map_t *const map, const char *const key, void *val) {
  assert(map);
  map_val_t *map_val = map_val_new();

  map_val->key.s = malloc(sizeof(char) + strlen(key));
  assert(map_val->key.s);
  strcpy(map_val->key.s, key);

  map_val->type = TYPE_STRING;
  map_val->val = val;

  _map_resize(map);

  map->map[map->total++] = map_val;
}

void _map_add_key_int(map_t *const map, int key, void *val) {
  assert(map);
  map_val_t *map_val = map_val_new();

  map_val->key.i = key;
  map_val->type = TYPE_INT;
  map_val->val = val;

  _map_resize(map);

  map->map[map->total++] = map_val;
}

void _map_pushback_key_char(map_t *const map, char key, void *val, int size) {
  assert(map);
  assert(val);
  assert(size > 0);

  map_val_t *map_val = map_val_new();
  map_val->key.c = key;
  map_val->type = TYPE_CHAR;
  map_val->alloced = true;

  map_val->val = malloc(size);
  assert(map_val->val);
  memcpy(map_val->val, val, size);

  _map_resize(map);

  map->map[map->total++] = map_val;
}

void _map_pushback_key_string(map_t *const map, const char *const key,
                              void *val, int size) {
  assert(map);
  assert(val);
  assert(size > 0);

  map_val_t *map_val = map_val_new();

  map_val->key.s = malloc(sizeof(char) + strlen(key));
  assert(map_val->key.s);
  strcpy(map_val->key.s, key);
  map_val->type = TYPE_STRING;
  map_val->alloced = true;

  map_val->val = malloc(size);
  assert(map_val->val);
  memcpy(map_val->val, val, size);

  _map_resize(map);

  map->map[map->total++] = map_val;
}

void _map_pushback_key_int(map_t *const map, int key, void *val, int size) {
  assert(map);
  assert(val);
  assert(size > 0);

  map_val_t *map_val = map_val_new();

  map_val->key.i = key;
  map_val->type = TYPE_INT;
  map_val->alloced = true;

  map_val->val = malloc(size);
  assert(map_val->val);
  memcpy(map_val->val, val, size);

  _map_resize(map);

  map->map[map->total++] = map_val;
}

void *_map_get_key_char(map_t *const map, char key) {
  assert(map);

  for (int i = 0; i < map->total; i++) {
    map_val_t *val = map->map[i];

    if (val->type != TYPE_CHAR) {
      continue;
    }

    if (val->key.c == key) {
      return val->val;
    }
  }
  return NULL;
}

void *_map_get_key_string(map_t *const map, const char *const key) {
  assert(map);

  for (int i = 0; i < map->total; i++) {
    map_val_t *val = map->map[i];

    if (val->type != TYPE_STRING) {
      continue;
    }

    if (strcmp(val->key.s, key) == 0) {
      return val->val;
    }
  }
  return NULL;
}

void *_map_get_key_int(map_t *const map, int key) {
  assert(map);

  for (int i = 0; i < map->total; i++) {
    map_val_t *val = map->map[i];

    if (val->type != TYPE_INT) {
      continue;
    }

    if (val->key.i == key) {
      return val->val;
    }
  }
  return NULL;
}
