#include <iostream>
#include <vector>
#include "products/apple.h"
#include "market_data/market_data_engine.h"
#include "arbitrage.h"

int main() {
    std::vector<std::shared_ptr<Apple>> apples;
    apples.resize(10);
    for(int i = 0; i < 10; ++i) {
        apples[i] = std::make_shared<Apple>(i);
    }
    MarketDataEngine<Apple> market_date_engine(apples);
    Arbitrage<Apple> arbitrage(apples);
    for (int d = 0; d < 10; ++d) {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "----------Day " << d << "----------" << std::endl;
        for (int i = 0; i < 10; ++i) {
            std::cout << apples[i]->id_ << " bid=" << apples[i]->bid_ << " ask=" << apples[i]->ask_ << std::endl;
        }
        const ProfitTable& profit_table = arbitrage.getProfitTable();
        const std::vector<std::pair<double, double>>& snapshots = arbitrage.getProductsSnapshots();
        for (int i = 0; i < 10; ++i) {
            for(int j = 0; j < 10; ++j) {
                if (profit_table[i][j] > 0) {
                    std::cout << "buy in " << i << " at " << snapshots[i].second << " and sell in " << j << " at " << snapshots[j].first << std::endl;
                }
            }
        }
    }
    return 0;
}
