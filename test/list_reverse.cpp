#include <list>
#include <vector>
#include <algorithm>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <common/list.h>
#include <list/reverse/list_reverse.h>

using list_t = std::list<int>;

static constexpr int g_max_test_list_size = 1000;

auto create_arithmetic_progression(int size) {
    std::vector<int> res(size);
    auto i = 0;

    for (auto it = res.begin(); it != res.end(); ++it, ++i) {
        *it = i;
    }

    return res;
}

node* create_list(int size) {
    node* head = create_node(0);
    node* cur = head;
    head->next = nullptr;

    for (int i = 1; i < size; ++i) {
        cur->next = create_node(i);
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

TEST_P(list_reverse, reverse) {
    auto current_list = create_list(GetParam());
    auto orig_list = convert_list(current_list);

    current_list = reverse(current_list);
    check_reversed_list(orig_list, convert_list(current_list));
    delete_list(current_list);
}

INSTANTIATE_TEST_CASE_P(parametrized_test, list_reverse,
                        ::testing::ValuesIn(create_arithmetic_progression(g_max_test_list_size)));
