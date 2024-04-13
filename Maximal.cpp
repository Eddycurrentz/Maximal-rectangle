#include <vector>
#include <stack>
using namespace std;

class Solution {
public:
    // Function to compute the maximal rectangle area in a 2D binary matrix
    int maximalRectangle(vector<vector<char>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return 0;  // handle empty matrix input
      
        int num_columns = matrix[0].size();
        vector<int> heights(num_columns, 0);
        int max_area = 0;

        // Process each row of the matrix
        for (auto& row : matrix) {
            // Update the heights of the histogram representation
            for (int j = 0; j < num_columns; ++j) {
                if (row[j] == '1') {
                    ++heights[j];  // Increase height for continuous '1's
                } else {
                    heights[j] = 0;  // Reset height if '0' is encountered
                }
            }
            // Get the max rectangle area in histogram and update max_area
            max_area = max(max_area, largestRectangleArea(heights));
        }
        return max_area;
    }

    // Helper function to calculate the area of the largest rectangle in a histogram
    int largestRectangleArea(vector<int>& heights) {
        int result = 0;
        int n = heights.size();
        stack<int> index_stack;
        vector<int> left(n, -1);
        vector<int> right(n, n);

        // Calculate the indices of the next smaller element on the left and right
        for (int i = 0; i < n; ++i) {
            while (!index_stack.empty() && heights[index_stack.top()] >= heights[i]) {
                right[index_stack.top()] = i;  // Update right index
                index_stack.pop();
            }
            left[i] = index_stack.empty() ? -1 : index_stack.top();  // Update left index
            index_stack.push(i);
        }
      
        // Compute the area for each bar considering the range [left, right]
        for (int i = 0; i < n; ++i) {
            result = max(result, heights[i] * (right[i] - left[i] - 1));
        }
      
        return result;
    }
};
