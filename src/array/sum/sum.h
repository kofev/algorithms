#include <vector>
#include <cstdint>

using number_array = std::vector<int>;
using sum_type = int64_t; // amd64 only

sum_type simple_calc_sum(const int* ptr, size_t size);
sum_type simple_calc_sum(const number_array& arr);
sum_type fast_calc_sum(const int* ptr, size_t size);
sum_type fast_calc_sum(const number_array& arr);
sum_type multithread_simple_calc_sum(const number_array& arr);
sum_type multithread_fast_calc_sum(const number_array& arr);
