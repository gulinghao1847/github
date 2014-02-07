/*
Unique Paths Total Accepted: 5085 Total Submissions: 16807 My Submissions
A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

How many possible unique paths are there?


Above is a 3 x 7 grid. How many possible unique paths are there?

Note: m and n will be at most 100.
*/
class Solution {
public:
    int uniquePaths(int m, int n) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        vector<vector<int>> grid(m, vector<int>(n, INT_MAX));
        
        for(int i = 0; i < m; i++) grid[i][0] = 1;
        for(int i = 0; i < n; i++) grid[0][i] = 1;
        
        for(int i = 1; i < m; i++){
            for(int j = 1; j < n; j++){
                grid[i][j] = grid[i - 1][j] + grid[i][j - 1];
            }
        }
        return grid[m - 1][n - 1];
    }
};

