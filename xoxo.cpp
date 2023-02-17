#include <iostream>
#include <sstream>

// O(countFirstChar + countSecondChar)

// Define the variables
const int MAX_CONSECUTIVE_COUNT = 4;
const char FIRST_CHAR = 'X';
const char SECOND_CHAR = 'O';
const int COUNT_FIRST_CHAR = 6;
const int COUNT_SECOND_CHAR = 1;

std::string generateString(int countFirstChar, int countSecondChar, int maxConsecutiveCount, char firstChar, char secondChar) {
    if (countFirstChar < 0 || countSecondChar < 0 || maxConsecutiveCount <= 0) {
        return "Invalid input: countFirstChar, countSecondChar, and maxConsecutiveCount must be non-negative, maxConsecutiveCount must be positive.";
    }

    int maxCount = std::max(countFirstChar, countSecondChar);
    int minCount = std::min(countFirstChar, countSecondChar);
    if (maxCount > (maxConsecutiveCount - 1) * (minCount + 1) + minCount) {
        return "Invalid input: impossible to generate string with no more than maxConsecutiveCount consecutive characters.";
    }

    std::stringstream result;
    char lastChar = ' ';
    int consecutiveCount = 0;

    while (countFirstChar > 0 || countSecondChar > 0) {
        if (countFirstChar > 0 && lastChar == firstChar && consecutiveCount >= maxConsecutiveCount - 1) {
            result << secondChar;
            lastChar = secondChar;
            countSecondChar--;
            consecutiveCount = 0;
        } else if (countSecondChar > 0 && lastChar == secondChar && consecutiveCount >= maxConsecutiveCount - 1) {
            result << firstChar;
            lastChar = firstChar;
            countFirstChar--;
            consecutiveCount = 0;
        } else {
            if (countFirstChar > countSecondChar) {
                result << firstChar;
                lastChar = firstChar;
                countFirstChar--;
            } else {
                result << secondChar;
                lastChar = secondChar;
                countSecondChar--;
            }
            consecutiveCount++;
        }
    }

    return result.str();
}

int main() {
    std::string xoxo = generateString(COUNT_FIRST_CHAR, COUNT_SECOND_CHAR, MAX_CONSECUTIVE_COUNT, FIRST_CHAR, SECOND_CHAR);
    std::cout << xoxo << std::endl;
    return 0;
}
