#include "node.h"

#include <stdlib.h>

node* create_node(int val) {
    node* ptr = (node*)malloc(sizeof(node));
    ptr->value = val;
    return ptr;
}

void delete_node(node* ptr) {
    free(ptr);
}
