#include <iostream>

int main() {
    std::string cities[] = {
        "Beijing", "Shanghai", "Guangzhou", "Shenzhen", "Chengdu",
        "Chongqing", "Wuhan", "Xi'an", "Hangzhou", "Nanjing"
    };

    std::cout << "Here are ten cities in China:\n";
    for (const std::string& city : cities) {
        std::cout << city << std::endl;
    }

    return 0;
}
