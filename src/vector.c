/**********************************************************
 * This file is part of cutil.
 *
 * cutil is free software: you can redistribute it and/or modify 
 * it under the terms of the GNU General Public License 
 * as published by the Free SoftwareFoundation, either version 3 
 * of the License, or (at your option) any later version.
 * 
 * cutil is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License 
 * along with cutil. If not, see <https://www.gnu.org/licenses/>.
 **********************************************************/

#include <cutil/vector.h>

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>

#define VECTOR_INIT_CAPACITY 4

struct vector_t {
    void **items;
    int capacity;
    int total;
};

vector_t *
vector_new(void) {
    vector_t *vector = malloc(sizeof(vector_t));
    assert(vector);

    vector->capacity = VECTOR_INIT_CAPACITY;
    vector->total = 0;
    vector->items = malloc(sizeof(void *) * vector->capacity);
    assert(vector->items);

    return vector;
}

void
vector_destroy(vector_t *vector) {
    assert(vector);

    free(vector->items);
    free(vector);
}

int
vector_size(vector_t *vector) {
    assert(vector);
    return vector->total;
}

void
vector_resize(vector_t *vector, int capacity) {
    void **items = realloc(vector->items, sizeof(void *) * capacity);
    assert(items);

    vector->items = items;
    vector->capacity = capacity;
}

void
vector_add(vector_t *vector, void *item) {
    assert(vector);
    assert(item);

    if (vector->total == vector->capacity) {
        vector_resize(vector, vector->capacity * 2);
    }

    vector->items[vector->total++] = item;
}

void
vector_addv_(vector_t *vector, int count, ...) {
    assert(vector);

    va_list args;
    int i = 0;

    --count;
    va_start(args, count);

    for (i = 0; i < count; ++i) {
        void *item = va_arg(args, void *);
        vector_add(vector, item);
    }

    va_end(args);
}

void
vector_pushback(vector_t *vector, void *item, int size) {
    assert(vector);
    assert(item);
    assert(size > 0);

    if (vector->total == vector->capacity) {
        vector_resize(vector, vector->capacity * 2);
    }

    void *item_ptr = malloc(sizeof(size));
    assert(item_ptr);
    memcpy(item_ptr, item, size);

    vector->items[vector->total++] = item_ptr;
}

void 
vector_push_string(vector_t *vector, const char *str) {
    assert(vector);
    assert(str);

    if (vector->total == vector->capacity) {
        vector_resize(vector, vector->capacity * 2);
    }

    void *item = malloc(sizeof(char) + strlen(str));
    assert(item);
    strcpy(item, str);

    vector->items[vector->total++] = item;
}

void
vector_delete(vector_t *vector, int index) {
    assert(vector);
    if (index < 0 || index >= vector->total) {
        return;
    }

    vector->items[index] = NULL;

    for (int i = index; i < vector->total - 1; i++) {
        vector->items[i] = vector->items[i + 1];
        vector->items[i + 1] = NULL;
    }

    vector->total--;

    if (vector->total > 0 && vector->total == vector->capacity / 4) {
        vector_resize(vector, vector->capacity / 2);
    }
}

void *
vector_get(vector_t *vector, int index) {
    assert(vector);

    if (index >= 0 && index < vector->total) {
        return vector->items[index];
    }
    return NULL;
}
