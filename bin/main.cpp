//
// Created by Святослав on 21.03.2024.
//
#include "lib/Range.h"
#include <vector>
#include <set>
#include <ranges>
#include <map>


int main() {
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::map<int, int> s = {{1,1}, {2,2}};
    
    Range<std::vector<int>::iterator> my_wrapper = v | take(5);
    auto ranges_wrapper = v | std::ranges::views::take(5);
    
    std::vector<int> lab_res;
    std::vector<int> ranges_res;
    for (auto i : my_wrapper) {
        lab_res.push_back(i);
    }
    for (auto i : ranges_wrapper) {
        ranges_res.push_back(i);
    }
    
}
