#ifndef PRIME_GENERATOR_H
#define PRIME_GENERATOR_H

#include <vector>
#include <stdexcept>

inline std::vector<int> prime_sizes = {29}; // Initial primes in descending order

inline void set_primes(const std::vector<int> &primes) {
    prime_sizes = primes;
}

inline int get_next_size() {
    if (prime_sizes.empty()) {
        throw std::runtime_error("No more primes available for resizing.");
    }
    int next = prime_sizes.back();
    prime_sizes.pop_back();
    return next;
}

#endif // PRIME_GENERATOR_H
