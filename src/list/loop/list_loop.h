#ifndef ALGORITHMS_LIST_LOOP_H
#define ALGORITHMS_LIST_LOOP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <list/node.h>

node* find_loop(node* head);
void find_and_remove_loop(node* head);

#ifdef __cplusplus
}
#endif

#endif // ALGORITHMS_LIST_LOOP_H
