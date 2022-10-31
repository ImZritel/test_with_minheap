#pragma once

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std::string_literals;

void TestResult(const std::vector<int>& result, int X, const std::set<int>& allPossibleEntries, 
    const std::string& r_str, const std::string& p_str, const std::string& file, const std::string& func, unsigned line, const std::string& hint) {
    bool isPossible = true;
    // Each ID from the result must exist in the test std::set.
    for (auto el : result) {
        if (allPossibleEntries.count(el) == 0) {
            isPossible = false;
            break;
        }
    }
    // The number of IDs in the result must be either equal to X or the number of records submitted for input. And "isPossible"
    if (((result.size() != X && X <= allPossibleEntries.size()) 
        && (result.size() != allPossibleEntries.size() && X > allPossibleEntries.size())) 
        || !isPossible) {
        std::cout << std::boolalpha;
        std::cout << file << "("s << line << "): "s << func << ": "s;
        std::cout << "TEST_RESULT("s << r_str << ", "s << p_str << ") failed."s;
        if (!hint.empty()) {
            std::cout << " Hint: "s << hint;
        }
        std::cout << std::endl;
        abort();
    }
}
