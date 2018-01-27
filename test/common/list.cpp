#include <iostream>

#include "list.h"

void delete_list(node* list) {
    node* tmp = nullptr;

    if (list != nullptr) {
        while (list->next != nullptr) {
            tmp = list->next;
            delete_node(list);
            list = tmp;
        }

        delete_node(list);
    }
}

void print_list(node* first) {
    if (first != nullptr) {
        while (first->next != nullptr) {
            std::cout << first->value << ", ";
            first = first->next;;
        }

        std::cout << first->value << std::endl;
    }
}
