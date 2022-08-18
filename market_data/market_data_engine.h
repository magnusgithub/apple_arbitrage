//
// Created by Magnus Lam on 18/8/2022.
//

#ifndef APPLE_ARBITRAGE_MARKET_DATA_ENGINE_H
#define APPLE_ARBITRAGE_MARKET_DATA_ENGINE_H

#include <vector>
#include <thread>
#include <random>

template <class Product>
class MarketDataEngine {
public:
    explicit MarketDataEngine(std::vector<std::shared_ptr<Product>>& products) : products_(products) {
        update_threads_.reserve(products.size());
        for (int i = 0; i < products.size(); ++i) {
            update_threads_[i] = std::thread(MarketDataEngine::UpdateMarketDate, products[i], i);
            update_threads_[i].detach();
        }
    }
private:
    [[noreturn]] static void UpdateMarketDate(std::shared_ptr<Product> product, int seed) {
        std::mt19937_64 mtEngine(seed);
        std::normal_distribution<> nd;
        while (true) {
            std::this_thread::sleep_for(std::chrono::milliseconds (50));
            product->price_ = GetNextPrice(*product, nd(mtEngine));
            product->bid_ = product->price_ * (1 - product->spread_ / 2.0);
            product->ask_ = product->price_ * (1 + product->spread_ / 2.0);
        }
    }
    static double GetNextPrice(const Product& product, double norm) {
        double expArg1 = (product.risk_free_rate_ - ((product.volatility_ * product.volatility_) / 2.0)) * delta_t;
        double expArg2 = product.volatility_ * norm * sqrt(delta_t);
        return product.price_ * exp(expArg1 + expArg2);
    }
    const std::vector<std::shared_ptr<Product>> products_;
    std::vector<std::thread> update_threads_;
    static const int delta_t = 1;
};


#endif //APPLE_ARBITRAGE_MARKET_DATA_ENGINE_H
