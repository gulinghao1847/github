/*
Search a 2D Matrix Total Accepted: 8754 Total Submissions: 29114 My Submissions
Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:

Integers in each row are sorted from left to right.
The first integer of each row is greater than the last integer of the previous row.
For example,

Consider the following matrix:

[
  [1,   3,  5,  7],
  [10, 11, 16, 20],
  [23, 30, 34, 50]
]
Given target = 3, return true.
*/
class Solution {
public:
    bool searchMatrix(vector<vector<int> > &matrix, int target) {
        if(matrix.size() == 0 || matrix[0].size() == 0) return false;
        for(int i = 0; i < matrix.size(); i++){
            if(target < matrix[i][0]){
                break;
            }else if(target <= matrix[i][matrix[i].size() - 1]){
                for(int j = 0; j < matrix[i].size(); j++){
                    if(matrix[i][j] == target) return true;
                }    
            }
        }
        return false;
    }
};

