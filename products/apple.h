//
// Created by Magnus Lam on 18/8/2022.
//

#ifndef APPLE_ARBITRAGE_APPLE_H
#define APPLE_ARBITRAGE_APPLE_H

#include <atomic>

struct Apple {
    explicit Apple(int id) : id_(id) {}
    int id_;
    std::atomic<double> bid_ = 9.995;
    std::atomic<double> ask_ = 10.005;
    std::atomic<double> price_ = 10.0;
    constexpr static const double volatility_ = 0.005;
    constexpr static const double risk_free_rate_ = 0.01;
    constexpr static const double spread_ = 0.01;
};
#endif //APPLE_ARBITRAGE_APPLE_H
