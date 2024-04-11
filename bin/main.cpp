//
// Created by Святослав on 21.03.2024.
//
#include "lib/Range.h"
#include <vector>
#include <set>
#include <ranges>
#include <map>


int main() {
    
    std::vector<int> a = {1,2,3,4};

    auto x = (a | transform([](int i){return i * i;}));
    
    for (auto r : a | filter([](int i){return i % 2;})) {

        std::cout << r << " ";
    }
    
}
