#ifndef ALGORITHMS_NODE_H
#define ALGORITHMS_NODE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct node node;

struct node {
    int value;
    node* next;
};

node* create_node(int val);
void delete_node(node* ptr);

#ifdef __cplusplus
}
#endif

#endif // ALGORITHMS_NODE_H
