#include <list>
#include <vector>
#include <algorithm>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <list/reverse/list_reverse.h>

using list_t = std::list<int>;

class random_generator {
public:
    random_generator() {
        std::srand(std::time(nullptr));
    }

    int generate() {
        return std::rand() % std::numeric_limits<int>::max();
    }
};

static constexpr int g_max_test_list_size = 1000;
random_generator g_randomizer;

auto create_arithmetic_progression(int size) {
    std::vector<int> res(size);
    auto i = 0;

    for (auto it = res.begin(); it != res.end(); ++it, ++i) {
        *it = i;
    }

    return res;
}

void delete_list(node* list) {
    node* tmp = nullptr;

    if (list != nullptr) {
        while (list->next != nullptr) {
            tmp = list->next;
            delete list;
            list = tmp;
        }

        delete list;
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

node* create_list(int size) {
    node* head = nullptr;
    node* cur = nullptr;

    head = new node(g_randomizer.generate());
    head->next = nullptr;
    cur = head;

    for (int i = 1; i < size; ++i) {
        cur->next = new node(g_randomizer.generate());
        cur = cur->next;
    }

    cur->next = nullptr;
    return head;
}

list_t convert_list(node* list) {
    list_t converted;

    for (; list != nullptr; list = list->next) {
        converted.emplace_back(list->value);
    }

    return converted;
}

void check_reversed_list(list_t& current, const list_t& expected) {
    std::reverse(current.begin(), current.end());
    EXPECT_THAT(expected, ::testing::ElementsAreArray(current));
}

class list_reverse : public ::testing::TestWithParam<int> { };

TEST_P(list_reverse, parametrized_reverse) {
    auto current_list = create_list(GetParam());
    auto orig_list = convert_list(current_list);

//    print_list(current_list);
    current_list = reverse(current_list);
//    print_list(current_list);
    check_reversed_list(orig_list, convert_list(current_list));
    delete_list(current_list);
}

INSTANTIATE_TEST_CASE_P(parametrized_test, list_reverse,
                        ::testing::ValuesIn(create_arithmetic_progression(g_max_test_list_size)));
