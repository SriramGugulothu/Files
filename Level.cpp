#include <iostream>
#include <string>
#include <stack>
using namespace std;

// A structure to store a node's value and its depth level
struct Node {
    int value;
    int depth;
};

int main() {
    int targetLevel;   // The target depth (x)
    string treeStr;    // The string representation of the binary tree

    // Input the target level and tree string
    cin >> targetLevel;
    cin >> treeStr;

    // Variables to track the current state
    int currentLevel = 0;  // Tracks the depth level
    int currentValue = 0;  // Tracks the current number being formed
    bool isNegative = false; // Tracks if the number is negative
    bool numberInProgress = false;  // Indicates if a number is being formed

    int sumAtTargetLevel = 0;  // Sum of node values at level x+1

    // Traverse through the string
    for (char ch : treeStr) {
        if (ch == '(') {
            // When encountering '(', increase the depth
            currentLevel++;
        }
        else if (ch == ')') {
            // When encountering ')', complete the current number (if any) and decrease the depth
            if (numberInProgress) {
                // Apply the sign if the number was negative
                if (isNegative) {
                    currentValue = -currentValue;
                }

                // If this node is at the target depth (x + 1), add its value to the sum
                if (currentLevel == targetLevel + 1) {
                    sumAtTargetLevel += currentValue;
                }

                // Reset state for next potential number
                currentValue = 0;
                isNegative = false;
                numberInProgress = false;
            }

            // Decrease the depth
            currentLevel--;
        }
        else if (ch == '-') {
            // Mark the current number as negative
            isNegative = true;
            numberInProgress = true;
        }
        else if (isdigit(ch)) {
            // Continue building the number
            currentValue = currentValue * 10 + (ch - '0');
            numberInProgress = true;
        }
    }

    // Output the final result
    cout << sumAtTargetLevel << endl;

    return 0;
}

