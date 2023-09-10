#include <cutil/linked_list.h>
#include <stdlib.h>
#include <assert.h>

node_t *
linkedlist_new(void *val) {
    node_t *head = malloc(sizeof(node_t));
    assert(head);

    head->val = val;
    head->next = NULL;

    return head;
}

void
linkedlist_push(node_t *head, void *val) {
    node_t *current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = malloc(sizeof(node_t));
    current->next->val = val;
    current->next->next = NULL;
}
