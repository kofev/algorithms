#include "list_loop.h"

void delete_loop_nodes(node* loop_begin) {
    node* next = loop_begin->next->next;
    node* cur = loop_begin->next;

    while (next != loop_begin) {
        delete cur;
        cur = next;
        next = next->next;
    }

    delete cur;
}

node* find_loop(node* head) {
    node* slow = head;
    node* fast = head;
    node* res = nullptr;

    while (slow->next != nullptr && fast->next != nullptr && fast->next->next != nullptr) {
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
    loop->next = nullptr;
}

void find_and_remove_loop(node* head) {
    node* loop = find_loop(head);

    if (loop != nullptr) {
        remove_loop(loop);
    }
}
