#include <cutil/stack.h>

#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define STACK_INIT_CAPACITY 1

struct _stack_t {
    void **stack;
    int total;
    int capacity;
};

stack_t *stack_new(void) {
    stack_t *s = malloc(sizeof(stack_t));
    assert(s);
    
    s->total = 0;
    s->capacity = STACK_INIT_CAPACITY;
    s->stack = malloc(sizeof(void *) * s->capacity);
    assert(s->stack);

    return s;
}

int stack_size(stack_t *s) {
    assert(s);

    return s->total;
}

void _stack_resize(stack_t *s) {
    if (s->total != s->capacity) {
    return;
    }

    int capacity = s->capacity * 2;

    void **stack = realloc(s->stack, sizeof(void *) * capacity);
    assert(stack);

    s->stack = stack;
    s->capacity = capacity;
}

void stack_push(stack_t *s, void *p, int l) {
    assert(s);
    assert(p);
    assert(s > 0);

    void *data = malloc(l);
    assert(data);
    memcpy(data, p, l);

    s->stack[s->total++] = data;
}

void *stack_pop(stack_t *s) {
    assert(s);

    void *src = s->stack[s->total];
    int size = sizeof(src);
    void *data = malloc(size);
    assert(data);
    memcpy(data, src, size);

    free(src);

    return data;
}

void *stack_peek(stack_t *s) {
    assert(s);
    return s->stack[s->total];
}

void stack_destroy(stack_t *s) {
    for (int i = 0; i < s->total; i++) {
        free(s->stack[i]);
    }
    free(s->stack);
    free(s);
}
