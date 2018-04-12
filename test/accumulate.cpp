#include <common/randomizer.h>
#include <common/time_measurer.h>
#include <array/accumulate/accumulate.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <vector>

using test_value_type = uint32_t;
using test_data = std::vector<test_value_type>;
using result_type = uint64_t;

static constexpr int g_test_data_size = 100000001;

auto& get_data() {
    static test_data data(g_test_data_size, 0);
    return data;
}

template <typename fn_type>
void test_array(fn_type&& fn) {
    using randomizer_type = numeric_randomizer<test_value_type, 100>;

    randomizer_type rnd;
    auto& data = get_data();

    rnd.fill_container(data);
    result_type std_res = 0;
    std_res = std::accumulate(data.begin(), data.end(), std_res);

    result_type res = 0;
    print_execution_time(std::forward<fn_type>(fn), res, data);
    ASSERT_EQ(std_res, res);
}

//TEST(accumulate, base) {
//    auto fn = [](auto& res, const auto& data) {
//        auto fn = [](auto beg, auto end, auto init) {
//            return algorithms::accumulate(beg, end, init);
//        };
//        res = algorithms::parallel_accumulate_base(data.begin(), data.end(), res, fn); };
//    test_array(std::move(fn));
//}

TEST(accumulate, standard) {
    auto fn = [](auto& res, const auto& data) {
        res = algorithms::accumulate(data.begin(), data.end(), res); };
    test_array(std::move(fn));
}

TEST(accumulate, optimized) {
    auto fn = [](auto& res, const auto& data) {
        res = algorithms::optimized_accumulate(data.data(), data.size(), res); };
    test_array(std::move(fn));
}

TEST(accumulate, parallel) {
    auto fn = [](auto& res, const auto& data) {
        res = algorithms::parallel_accumulate(data.begin(), data.end(), res); };
    test_array(std::move(fn));
}

TEST(accumulate, parallel_optimized) {
    auto fn = [](auto& res, const auto& data) {
        res = algorithms::parallel_optimized_accumulate(
            data.data(), data.data() + data.size(), res);
    };
    test_array(std::move(fn));
}

//TEST(accumulate, parallel_optimized) {
//    auto fn = [](auto& res, const auto& data) {
//        res = algorithms::parallel_optimized_accumulate(data.data(), data.size(), res); };
//    test_array(std::move(fn));
//}
