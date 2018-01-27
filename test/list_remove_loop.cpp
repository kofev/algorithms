#include <vector>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <list/loop/list_loop.h>
#include <common/list.h>

static constexpr int g_max_test_list_size = 50;

using test_param_t = std::pair<int, int>;
using test_param_arr_t = std::vector<test_param_t>;

test_param_arr_t create_params(int max_list_size) {
    test_param_arr_t params;
    params.reserve(max_list_size * ((max_list_size + 1) * max_list_size) / 2);

    for (int i = 0; i < max_list_size; ++i) {
        for (int j = 1; j < max_list_size - i; ++j) {
            params.emplace_back(i, j);
        }
    }

    return params;
}

node* generate(const test_param_t& par) {
    node* head = create_node(0);
    node* cur = head;
    node* loop = nullptr;
    int i = 1;

    // Generate list body
    for (; i <= par.first; ++i) {
        cur->next = create_node(i);
        cur = cur->next;
    }

    loop = cur;

    // Generate list loop
    for (; i <= par.first + par.second; ++i) {
        cur->next = create_node(i);
        cur = cur->next;
    }

    cur->next = loop;

    return head;
}

class remove_list_loop : public ::testing::TestWithParam<test_param_t> { };

TEST_P(remove_list_loop, loop_remove) {
    auto current_list = generate(GetParam());
    find_and_remove_loop(current_list);
    ASSERT_EQ(nullptr, find_loop(current_list));
    delete_list(current_list);
}

INSTANTIATE_TEST_CASE_P(parametrized_test, remove_list_loop,
                        ::testing::ValuesIn(create_params(g_max_test_list_size)));
