/*
N-Queens Total Accepted: 5236 Total Submissions: 20885 My Submissions
The n-queens puzzle is the problem of placing n queens on an n×n chessboard such that no two queens attack each other.



Given an integer n, return all distinct solutions to the n-queens puzzle.

Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space respectively.

For example,
There exist two distinct solutions to the 4-queens puzzle:

[
 [".Q..",  // Solution 1
  "...Q",
  "Q...",
  "..Q."],

 ["..Q.",  // Solution 2
  "Q...",
  "...Q",
  ".Q.."]
]
*/
class Solution {
public:
    bool checkValid(int row, int column, int n, vector<int>& checkArray){
        for(int i = 0; i < row; i++){
            //check the diag
            if(abs(i - row) == abs(checkArray[i] - column) || checkArray[i] == column){
                return false;
            }
        }
        return true;
    }
    void run(vector<vector<string>>& result, vector<string>&now, int begin, int n, vector<int>& checkArray){
        if(begin == n){
            result.push_back(now);
            return;
        }
        
        for(int i = 0; i < n; i++){
            if(checkValid(begin, i, n, checkArray)){
                string s(n, '.');
                s[i] = 'Q';
                now.push_back(s);
                checkArray[begin] = i;
                run(result, now, begin + 1, n, checkArray);
                now.pop_back();
                checkArray[begin] = -1;
            }
        }
    }
    vector<vector<string>> solveNQueens(int n) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        vector<vector<string>> result;
        vector<int> checkArray(n, -1);
        vector<string> now;
        run(result, now, 0, n, checkArray);
        return result;
    }
};

