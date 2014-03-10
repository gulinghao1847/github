/*
Spiral Matrix Total Accepted: 4968 Total Submissions: 25129 My Submissions
Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.

For example,
Given the following matrix:

[
 [ 1, 2, 3 ],
 [ 4, 5, 6 ],
 [ 7, 8, 9 ]
]
You should return [1,2,3,6,9,8,7,4,5].
*/
class Solution {
private:
    int upB;
    int downB;
    int leftB;
    int rightB;
public:
    void goLeft(vector<int>& result, vector<vector<int>>& matrix){
        for(int i =leftB; i <= rightB; i++){
            result.push_back(matrix[upB][i]);
        }
        upB++;
    }
    void goDown(vector<int>& result, vector<vector<int>>& matrix){
        for(int i = upB; i <= downB; i++){
            result.push_back(matrix[i][rightB]);
        }
        rightB--;
    }
    void goRight(vector<int>& result, vector<vector<int>>& matrix){
        for(int i = rightB; i >= leftB; i--){
            result.push_back(matrix[downB][i]);
        }
        downB--;
    }
    void goUp(vector<int>& result, vector<vector<int>>& matrix){
        for(int i = downB; i >= upB; i--){
            result.push_back(matrix[i][leftB]);
        }
        leftB++;
    }
    vector<int> spiralOrder(vector<vector<int> > &matrix) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        vector<int> result;
        if(matrix.size() == 0) return result;
        upB = 0;
        downB = matrix.size() - 1;
        leftB = 0;
        rightB = matrix[0].size() - 1;
        while(upB <= downB && leftB <= rightB){
            if(upB <= downB && leftB <= rightB) goLeft(result, matrix);
            if(upB <= downB && leftB <= rightB) goDown(result, matrix);
            if(upB <= downB && leftB <= rightB) goRight(result, matrix);
            if(upB <= downB && leftB <= rightB) goUp(result, matrix);
        }
        return result;
    }
};

