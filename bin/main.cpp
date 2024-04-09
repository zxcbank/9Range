//
// Created by Святослав on 21.03.2024.
//
#include "lib/Range.h"
#include <vector>
#include <set>
#include <ranges>
#include <map>


int main() {
    
    std::map<std::string, int> a = {{"CPU", 10}, {"GPU", 15}, {"RAM", 20}};

    for (auto r : a | keys() ) {
        std::cout << r;
    }


}
