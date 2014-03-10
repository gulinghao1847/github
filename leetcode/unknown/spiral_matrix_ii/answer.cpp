/*
Spiral Matrix II Total Accepted: 5068 Total Submissions: 17077 My Submissions
Given an integer n, generate a square matrix filled with elements from 1 to n2 in spiral order.

For example,
Given n = 3,

You should return the following matrix:
[
 [ 1, 2, 3 ],
 [ 8, 9, 4 ],
 [ 7, 6, 5 ]
]
*/
class Solution {
private:
    int upB;
    int downB;
    int leftB;
    int rightB;
public:
    void goLeft(vector<vector<int>>& result, int& val){
        for(int i =leftB; i <= rightB; i++){
            result[upB][i] = val++;
        }
        upB++;
    }
    void goDown(vector<vector<int>>& result, int& val){
        for(int i = upB; i <= downB; i++){
            result[i][rightB] = val++;
        }
        rightB--;
    }
    void goRight(vector<vector<int>>& result, int& val){
        for(int i = rightB; i >= leftB; i--){
            result[downB][i] = val++;
        }
        downB--;
    }
    void goUp(vector<vector<int>>& result, int& val){
        for(int i = downB; i >= upB; i--){
            result[i][leftB] = val++;
        }
        leftB++;
    }
    vector<vector<int> > generateMatrix(int n) {
        vector<vector<int>> result(n, vector<int>(n, 0));
        if(n == 0) return result;
        int val = 1;
        upB = 0;
        downB = n - 1;
        leftB = 0;
        rightB = n - 1;
        while(upB <= downB && leftB <= rightB){
            if(upB <= downB && leftB <= rightB) goLeft(result,val);
            if(upB <= downB && leftB <= rightB) goDown(result,val);
            if(upB <= downB && leftB <= rightB) goRight(result,val);
            if(upB <= downB && leftB <= rightB) goUp(result,val);
        }
        return result;    
    }
};

