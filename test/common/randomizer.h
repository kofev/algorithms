#ifndef ALGORITHMS_RANDOMIZER_H
#define ALGORITHMS_RANDOMIZER_H

#include <numeric>
#include <time.h>
#include <random>
#include <algorithm>
#include <functional>

template <typename T, T max_val = std::numeric_limits<T>::max()>
class numeric_randomizer {
public:
    static_assert(std::numeric_limits<T>::is_integer, "Wrong random data type");

    virtual ~numeric_randomizer() = default;

    numeric_randomizer() {
        ::srand(time(0));
        m_fn = []() { return static_cast<T>(::rand()) % max_val; };
    }

    T get_random() {
        return m_fn();
    }

    template <typename Container>
    void fill_container(Container& cont) {
        static_assert(std::is_same_v<typename Container::value_type, T>, "Wrong container type");
        std::generate(cont.begin(), cont.end(), m_fn);
    };

private:
    using random_func = std::function<T(void)>;

private:
    random_func m_fn;
};

#endif // ALGORITHMS_RANDOMIZER_H
