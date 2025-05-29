#include <iostream>

void drawRectangle(int width, int height, char ch) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            std::cout << ch;
        }
        std::cout << std::endl;
    }
}

int main() {
    int width, height;
    char ch;

    std::cout << "Enter width of rectangle: ";
    std::cin >> width;
    std::cout << "Enter height of rectangle: ";
    std::cin >> height;
    std::cout << "Enter character to draw rectangle: ";
    std::cin >> ch;

    drawRectangle(width, height, ch);

    return 0;
}

