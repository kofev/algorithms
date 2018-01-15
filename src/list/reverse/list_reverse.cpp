#include "list_reverse.h"

node* reverse(node* list) {
    node* prev = nullptr;
    node* tmp = nullptr;
    node* cur = list;

    if (cur != nullptr && cur->next != nullptr) {
        prev = cur;
        cur = cur->next;

        while (cur->next != nullptr) {
            tmp = cur->next;
            cur->next = prev;
            prev = cur;
            cur = tmp;
        }

        cur->next = prev;
        list->next = nullptr;
    }

    return cur;
}
