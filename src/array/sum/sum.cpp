#include "sum.h"

#include <thread>
#include <future>
#include <iostream>

sum_type simple_calc_sum(const int* ptr, size_t size) {
    sum_type sum = 0;

    for (decltype(size) i = 0; i < size; ++i) {
        sum += ptr[i];
    }

    return sum;
}

sum_type simple_calc_sum(const number_array& arr) {
    return simple_calc_sum(arr.data(), arr.size());
}

sum_type fast_calc_sum(const int* ptr, size_t size) {
    static constexpr size_t acc_number = 8;
    decltype(size) max_index = size - acc_number + 1;
    decltype(size) i = 0;
    sum_type acc1 = 0;
    sum_type acc2 = 0;
    sum_type acc3 = 0;
    sum_type acc4 = 0;
    sum_type acc5 = 0;
    sum_type acc6 = 0;
    sum_type acc7 = 0;
    sum_type acc8 = 0;

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
        }
    }

    while (i < size) {
        acc1 += ptr[i++];
    }

    return acc1 + acc2 + acc3 + acc4 + acc5 + acc6 + acc7 + acc8;
}

sum_type fast_calc_sum(const number_array& arr) {
    return fast_calc_sum(arr.data(), arr.size());
}

struct array_part {
    const int* ptr;
    size_t size;
};

using array_parts = std::vector<array_part>;

array_parts get_parts(const number_array& arr, size_t num) {
    array_parts parts{};
    auto ptr = arr.data();
    auto part_size = arr.size() / num;
    auto last_part_size = arr.size() % num;

    for (decltype(num) i = 0; i < num - 1; ++i) {
        parts.emplace_back(array_part {ptr + part_size * i, part_size});
    }

    parts.emplace_back(array_part {ptr + part_size * (num - 1), part_size + last_part_size});

    return parts;
}

using future_array = std::vector<std::future<sum_type>>;

template <typename fn_type>
sum_type multithread_calc_sum(const number_array& arr, fn_type&& func) {
    future_array futures {};
    auto thread_cnt = std::thread::hardware_concurrency();
    auto parts = get_parts(arr, thread_cnt);
    sum_type sum = 0;

    for (auto& part : parts) {
        futures.emplace_back(std::async(std::launch::async,
                                        std::forward<fn_type>(func), part.ptr, part.size));
    }

    for (auto& fut : futures) {
        sum += fut.get();
    }

    return sum;
}

sum_type multithread_simple_calc_sum(const number_array& arr) {
    return multithread_calc_sum(arr, [](const int* ptr, size_t size)
        { return simple_calc_sum(ptr, size); });
}

sum_type multithread_fast_calc_sum(const number_array& arr) {
    return multithread_calc_sum(arr, [](const int* ptr, size_t size)
        { return fast_calc_sum(ptr, size); });
}
