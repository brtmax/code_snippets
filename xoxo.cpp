#include <string>
#include <iostream>
#include <utility>
#include <algorithm>
#include <vector>
#include <queue>

// comparison function for the priority queue
struct CompareCounts {
    bool operator()(const std::pair<int, char>& a, const std::pair<int, char>& b) const {
        return a.first < b.first;
    }
};

std::string generateString(std::initializer_list<std::pair<int, char>> counts) {
    std::string result;
    int total_count = 0;
    // initialize a priority queue to track the remaining counts of each character type
    std::priority_queue<std::pair<int, char>, std::vector<std::pair<int, char>>, CompareCounts> counts_queue;
    // populate the priority queue with the input counts and comute the total count of characters to generate
    for (const auto& count : counts) {
        counts_queue.push(count);
        total_count += count.first;
    }
    // generate the characters by repeatedly popping the character type with the smallest remaining count from the priority queue
    for (int i = 0; i < total_count; i++) {
        // pop the character type with the smallest remaining count from the priority queue
        auto count = counts_queue.top();
        counts_queue.pop();
        // append a character of this type to the result string
        result += count.second;
        // decrement the count and push the character type back onto the priority queue if the count is still greatdr than zero
        count.first--;
        if (count.first > 0) {
            counts_queue.push(count);
        }
    }
    return result;
}

int main() {
    std::string xoxo = generateString({{3, 'X'}, {2, 'O'}});
    std::cout << xoxo << std::endl;
    return 0;
}
