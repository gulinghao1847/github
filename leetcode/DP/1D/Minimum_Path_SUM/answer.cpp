/*
Minimum Path Sum Total Accepted: 2465 Total Submissions: 8178 My Submissions
Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right which minimizes the sum of all numbers along its path.

Note: You can only move either down or right at any point in time.
*/
class Solution {
public:
    int run(vector<vector<int>>& grid, int row, int column, vector<vector<int>>& matrix){
        if(row < 0  || column < 0){
            return INT_MAX;
        }
        if(matrix[row][column] != -1){
            return matrix[row][column];
        }
        matrix[row][column] = min(run(grid, row -1, column, matrix), run(grid, row, column - 1, matrix)) + grid[row][column];
        return matrix[row][column];
    }
    int minPathSum(vector<vector<int> > &grid) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        int s1 = grid.size();
        if(s1 == 0) return 0;
        int s2 = grid[0].size();
        vector<vector<int>> matrix(s1, vector<int>(s2, -1));
        matrix[0][0] = grid[0][0];
        return run(grid, s1 - 1, s2 - 1,matrix);
    }
};

