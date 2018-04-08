#include <common/time_measurer.h>
#include <array/sum/sum.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <vector>
#include <numeric>
#include <time.h>

using test_data = number_array;
static constexpr int g_test_data_size = 100000000;

template <int array_size = g_test_data_size>
class sum_checker{
public:
    sum_checker() = default;
    sum_checker(sum_checker&&) = delete;
    sum_checker& operator=(sum_checker&&) = delete;
    sum_checker(const sum_checker&) = delete;
    sum_checker& operator=(const sum_checker&) = delete;

public:
    void check_sum(sum_type cur_sum) {
        ASSERT_EQ(m_stl_sum, cur_sum);
    }

    auto get_data() const {
        return m_data;
    }

private:
    test_data generate_random_data(int size) {
        static constexpr int max_element = 100;
        test_data arr;
        arr.reserve(size);
        ::srand(::time(0));

        for (auto i = 0; i < size; ++i) {
            arr.push_back(::rand() % max_element);
        }

        return arr;
    }

    sum_type calc_stl_sum() {
        sum_type sum = 0;
        sum = std::accumulate(m_data.begin(), m_data.end(), sum);
        return sum;
    }

private:
    const test_data m_data = generate_random_data(array_size);
    const sum_type m_stl_sum = calc_stl_sum();
};

auto& get_checker() {
    static sum_checker checker{};
    return checker;
}

template <typename fn_type>
void test_array_sum(fn_type&& fn) {
    auto& checker = get_checker();
    auto data = checker.get_data();
    sum_type sum = 0;
    print_execution_time(std::forward<fn_type>(fn), sum, data);
    checker.check_sum(sum);
}

TEST(array_sum, simple) {
    auto fn = [](sum_type& sum, const test_data& data) { sum = simple_calc_sum(data); };
    test_array_sum(std::move(fn));
}

TEST(array_sum, fast) {
    auto fn = [](sum_type& sum, const test_data& data) { sum = fast_calc_sum(data); };
    test_array_sum(std::move(fn));
}

TEST(array_sum, multithread_simple) {
    auto fn = [](sum_type& sum, const test_data& data) { sum = multithread_simple_calc_sum(data); };
    test_array_sum(std::move(fn));
}

TEST(array_sum, multithread_fast) {
    auto fn = [](sum_type& sum, const test_data& data) { sum = multithread_fast_calc_sum(data); };
    test_array_sum(std::move(fn));
}
