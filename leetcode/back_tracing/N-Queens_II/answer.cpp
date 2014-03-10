/*
N-Queens II Total Accepted: 4632 Total Submissions: 15461 My Submissions
Follow up for N-Queens problem.

Now, instead outputting board configurations, return the total number of distinct solutions.


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
    void run(int begin, int n, vector<int>& checkArray, int& count){
        if(begin == n){
            count++;
            return;
        }
        
        for(int i = 0; i < n; i++){
            if(checkValid(begin, i, n, checkArray)){
                checkArray[begin] = i;
                run(begin + 1, n, checkArray, count);
                checkArray[begin] = -1;
            }
        }
    }
    int totalNQueens(int n) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        int count = 0;
        vector<int> checkArray(n, -1);
       // vector<string> now;
        run(0, n, checkArray, count);
        return count;
    }
};

