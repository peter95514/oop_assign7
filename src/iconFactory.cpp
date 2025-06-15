// TODO implementation
#include "iconFactory.h"
#include "icon.h"
#include <vector>

Icon IconFactory::Block_icon (int width, int height, Color color, std::string ascii) {
    Icon product;
    for (int i = 0; i < height; i ++) {
        std::vector<Cell> temp;
        for (int k = 0; k < width; k++) {
            temp.push_back(Cell(color, ascii));
        }
        product.push_back(temp);
    }
    return product;
}

Icon IconFactory::Player_icon (int width, int height, Color color, std::string ascii) {
    Icon product;
    for (int i = 0; i < height; i ++) {
        std::vector<Cell> temp;
        for (int k = 0; k < width; k++) {
            temp.push_back(Cell(color, ascii));
        }
        product.push_back(temp);
    }
    return product;
}
