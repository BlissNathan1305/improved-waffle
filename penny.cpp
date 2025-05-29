#include <iostream>
#include <vector>
#include <string>

// Function to simulate fetching stock data
std::vector<std::pair<std::string, double>> getPennyStocks() {
    return {
        {"Stock A", 0.85}, {"Stock B", 1.20}, {"Stock C", 0.95},
        {"Stock D", 1.50}, {"Stock E", 0.75}
    };
}

// Function to filter stocks based on price threshold
void findBestPennyStocks(const std::vector<std::pair<std::string, double>>& stocks, double maxPrice) {
    std::cout << "Best penny stocks under $" << maxPrice << ":\n";
    for (const auto& stock : stocks) {
        if (stock.second <= maxPrice) {
            std::cout << stock.first << " - $" << stock.second << std::endl;
        }
    }
}

int main() {
    std::vector<std::pair<std::string, double>> stocks = getPennyStocks();
    double maxPrice = 1.00; // Define penny stock threshold
    findBestPennyStocks(stocks, maxPrice);
    return 0;
}
