//
// Created by Magnus Lam on 18/8/2022.
//

#include "arbitrage.h"
#include "products/apple.h"

template<class Product>
void Arbitrage<Product>::Snap() {
    for(int i = 0; i < products_size_; ++i) {
        products_snapshots_[i].first = products_[i]->bid_;
        products_snapshots_[i].second = products_[i]->ask_;
    }
}

template<class Product>
void Arbitrage<Product>::PopulateProfitTable() {
    for (int i = 0; i < products_size_; ++i) {
        for (int j = 0; j < products_size_; ++j) {
            profit_table_[i][j] = products_snapshots_[i].second - products_snapshots_[j].first; // far touch
        }
    }
}

template<class Product>
const ProfitTable &Arbitrage<Product>::getProfitTable() {
    Snap();
    PopulateProfitTable();
    return profit_table_;
}

template<class Product>
const std::vector<std::pair<double, double>> &Arbitrage<Product>::getProductsSnapshots() const {
    return products_snapshots_;
}

template class Arbitrage<Apple>;