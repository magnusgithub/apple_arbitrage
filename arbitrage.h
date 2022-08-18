//
// Created by Magnus Lam on 18/8/2022.
//

#ifndef APPLE_ARBITRAGE_ARBITRAGE_H
#define APPLE_ARBITRAGE_ARBITRAGE_H

#include <vector>

typedef std::vector<std::vector<double>> ProfitTable; // for the cell in row i and column j, meaning buy Product i and sell Product j

template <class Product> // Products in different markets
class Arbitrage {
public:
    explicit Arbitrage(std::vector<std::shared_ptr<Product>>& products) : products_(products), products_size_(products.size()) {
        profit_table_ = std::vector<std::vector<double>>(products_size_, std::vector<double>(products_size_, 0.0));
        products_snapshots_.resize(products_size_);
    }
    [[nodiscard]] const ProfitTable& getProfitTable();
    [[nodiscard]] const std::vector<std::pair<double, double>>& getProductsSnapshots() const;
private:
    void PopulateProfitTable();
    void Snap();
    const std::vector<std::shared_ptr<Product>> products_;
    std::vector<std::pair<double, double>> products_snapshots_;
    ProfitTable profit_table_;
    const size_t products_size_;
};



#endif //APPLE_ARBITRAGE_ARBITRAGE_H
