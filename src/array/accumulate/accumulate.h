#include <vector>
#include <cstdint>
#include <future>

namespace algorithms {

template <typename InputIt, typename T>
T accumulate(InputIt first, InputIt last, T init) {
    for (; first != last; ++first) {
        init += *first;
    }

    return init;
};

template <typename T, typename Size, typename Sum>
Sum optimized_accumulate(const T* ptr, Size size, Sum init) {
    constexpr Size acc_number = 14; // 16 64-bit processor registers can be used
    Size max_index = size - acc_number + 1;
    Size i = 0;
    Sum acc1 = 0;
    Sum acc2 = 0;
    Sum acc3 = 0;
    Sum acc4 = 0;
    Sum acc5 = 0;
    Sum acc6 = 0;
    Sum acc7 = 0;
    Sum acc8 = 0;
    Sum acc9 = 0;
    Sum acc10 = 0;
    Sum acc11 = 0;
    Sum acc12 = 0;
    Sum acc13 = 0;
    Sum acc14 = 0;

    if (size >= acc_number) {
        for (; i < max_index; i += acc_number) {
            acc1 += ptr[i];
            acc2 += ptr[i + 1];
            acc3 += ptr[i + 2];
            acc4 += ptr[i + 3];
            acc5 += ptr[i + 4];
            acc6 += ptr[i + 5];
            acc7 += ptr[i + 6];
            acc8 += ptr[i + 7];
            acc9 += ptr[i + 8];
            acc10 += ptr[i + 9];
            acc11 += ptr[i + 10];
            acc12 += ptr[i + 11];
            acc13 += ptr[i + 12];
            acc14 += ptr[i + 13];
        }
    }

    while (i < size) {
        acc1 += ptr[i++];
    }

    return init + acc1 + acc2 + acc3 + acc4 + acc5 + acc6 + acc7
           + acc8 + acc9 + acc10 + acc11 + acc12 + acc13 + acc14;
}

namespace detail {

template <typename InputIt, typename T, typename CalcFunc>
T parallel_accumulate_base(InputIt first, InputIt last, T init, CalcFunc& fn) {
    using future_array = std::vector<std::future<T>>;

    constexpr unsigned long min_elem_per_thread = 100;
    constexpr unsigned long default_hardware_thread_cnt = 2;
    const unsigned long elem_cnt = std::distance(first, last);

    if (!elem_cnt) {
        return init;
    }

    const unsigned long hardware_thread_cnt = std::thread::hardware_concurrency();
    const unsigned long max_thread_cnt = (elem_cnt + min_elem_per_thread - 1) / min_elem_per_thread;
    const unsigned long thread_num = std::min(
        hardware_thread_cnt != 0 ? hardware_thread_cnt : default_hardware_thread_cnt,
        max_thread_cnt);
    const auto part_size = elem_cnt / thread_num;
    future_array result;
    result.reserve(thread_num);

    InputIt block_start = first;
    T init_val = 0;
    for (unsigned long i = 0; i < (thread_num - 1); ++i) {
        InputIt block_end = first;
        std::advance(block_end, part_size);
        result.push_back(
            std::async(std::launch::async, fn, block_start, block_end, init_val));

        block_start = block_end;
    }

    init = fn(block_start, last, init);

    for (auto& item : result) {
        init += item.get();
    }

    return init;
};

} // namespace detail

template <typename InputIt, typename T>
T parallel_accumulate(InputIt first, InputIt last, T init) {
    auto fn = [](auto beg, auto end, auto init) {
        return algorithms::accumulate(beg, end, init);
    };

    return detail::parallel_accumulate_base(first, last, init, fn);
};

template <typename InputIt, typename T>
T parallel_optimized_accumulate(InputIt first, InputIt last, T init) {
    auto fn = [](auto beg, auto end, auto init) {
        auto size = std::distance(beg, end);
        return algorithms::optimized_accumulate(beg, size, init);
    };

    return detail::parallel_accumulate_base(first, last, init, fn);
};

} // namespace algorithms
