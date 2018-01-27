#include <stddef.h>

#include "list_loop.h"

void delete_loop_nodes(node* loop_begin) {
    node* next = loop_begin->next->next;
    node* cur = loop_begin->next;

    while (next != loop_begin) {
        delete_node(cur);
        cur = next;
        next = next->next;
    }

    delete_node(cur);
}

node* find_loop(node* head) {
    node* slow = head;
    node* fast = head;
    node* res = NULL;

    while (slow->next != NULL && fast->next != NULL && fast->next->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            while (head != slow) {
                head = head->next;
                slow = slow->next;
            }

            res = slow;
            break;
        }
    }

    return res;
}

void remove_loop(node* loop) {
    delete_loop_nodes(loop);
    loop->next = NULL;
}

void find_and_remove_loop(node* head) {
    node* loop = find_loop(head);

    if (loop != NULL) {
        remove_loop(loop);
    }
}
