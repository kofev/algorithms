#ifndef LIST_REVERSE_H
#define LIST_REVERSE_H

struct node {
    node(int val)
        : value(val) {
    }

    int value;
    node* next = nullptr;
};

node* reverse(node* list);

#endif // LIST_REVERSE_H
