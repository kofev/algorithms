#include <stddef.h>

#include "list_reverse.h"

node* reverse(node* list) {
    node* prev = NULL;
    node* tmp = NULL;
    node* cur = list;

    if (cur != NULL && cur->next != NULL) {
        prev = cur;
        cur = cur->next;

        while (cur->next != NULL) {
            tmp = cur->next;
            cur->next = prev;
            prev = cur;
            cur = tmp;
        }

        cur->next = prev;
        list->next = NULL;
    }

    return cur;
}
