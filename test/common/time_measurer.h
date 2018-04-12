#ifndef ALGORITHMS_TIME_MEASURER_H
#define ALGORITHMS_TIME_MEASURER_H

#include <memory>
#include <chrono>
#include <iostream>

using namespace std::chrono;

template <typename fn_type, typename precision = microseconds>
class time_measurer {
public:
    time_measurer(fn_type&& fn)
        : m_functor(std::move(fn)) { }

    template <typename... arg_types>
    /*!
     * \brief Calculate function execution duration time
     * \tparam arg_types Argument types
     * \param args Arguments
     * \return Function execution duration time
     */
    auto operator()(arg_types&&... args) const {
        auto start = steady_clock::now();
        m_functor(std::forward<arg_types>(args)...);
        auto end = steady_clock::now();
        return duration_cast<precision>(end - start);
    }

private:
    fn_type m_functor;
};

template <typename fn_type, typename... arg_types>
void print_execution_time(fn_type&& fn, arg_types&&... args) {
    auto time = time_measurer(std::forward<fn_type>(fn))(std::forward<arg_types>(args)...);
    std::cout << "Execution time in microseconds: " << time.count();
}

#endif // ALGORITHMS_TIME_MEASURER_H
