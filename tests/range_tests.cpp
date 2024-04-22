//
// Created by Святослав on 18.04.2024.
//

#include "../lib/Range.h"
#include "gtest/gtest.h"
#include <ranges>


TEST(AdaptersTest, take_test) {
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::map<int, int> s = {{1,1}, {2,2}};
    auto my_wrapper = v | take(3);
    
    auto ranges_wrapper = v | std::ranges::views::take(3);

    std::vector<int> lab_res;
    std::vector<int> ranges_res;
    for (auto i : my_wrapper) {
        lab_res.push_back(i);
    }
    for (auto i : ranges_wrapper) {
        ranges_res.push_back(i);
    }

    ASSERT_EQ(lab_res, ranges_res);
}

TEST(AdaptersTest, trans_test) {
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::map<int, int> s = {{1,1}, {2,2}};
    
    auto my_wrapper = v | transform([](int i) { return i * 2; });
    
    
    
    auto ranges_wrapper = v | std::ranges::views::transform([](int i) { return i * 2; });
    
    std::vector<int> lab_res;
    std::vector<int> ranges_res;
    for (auto i : my_wrapper) {
        lab_res.push_back(i);
    }
    for (auto i : ranges_wrapper) {
        ranges_res.push_back(i);
    }
    
    ASSERT_EQ(lab_res, ranges_res);
}