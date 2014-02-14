/*
Search a 2D Matrix Total Accepted: 6135 Total Submissions: 20735 My Submissions
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
        int size1 = matrix.size();
        if(size1 == 0) return false;
        int size2 = matrix[0].size();
        for(int i = 0; i < size1; i++){
            for(int j = 0; j < size2; j++){
                if(target <= matrix[i][size2 - 1]){
                    for(int s = 0; s < matrix[i].size(); s++){
                        if(matrix[i][s] == target) return true;
                    }
                    return false;
                }else if(target > matrix[i][size2 - 1]){
                    continue;
                }
            }
        }
        return false;
    }
};
