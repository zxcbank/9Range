//
// Created by Святослав on 21.03.2024.
//
#include "lib/Range.h"
#include <vector>
#include <set>
#include <ranges>
#include <map>


int main() {

//    std::map<std::string, int> a = {{"CPU", 10}, {"GPU", 15}, {"RAM", 20}};
std::vector<std::pair<std::string, int>> a = {{"CPU", 10}, {"GPU", 15}, {"RAM", 20}};
//    std::set<int> a = {1,2,3,4};

    auto x = (a | reverse()).begin();
    
    for (auto r : a | values() | reverse() | take(2) ) {
        
        std::cout << r << " ";
    }
    
}
