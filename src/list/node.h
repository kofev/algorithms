#ifndef ALGORITHMS_NODE_H
#define ALGORITHMS_NODE_H

struct node {
    node(int val)
        : value(val) {
    }

    int value;
    node* next = nullptr;
};

#endif // ALGORITHMS_NODE_H
