/*
Surrounded Regions Total Accepted: 4702 Total Submissions: 33454 My Submissions
Given a 2D board containing 'X' and 'O', capture all regions surrounded by 'X'.

A region is captured by flipping all 'O's into 'X's in that surrounded region.

For example,
X X X X
X O O X
X X O X
X O X X
After running your function, the board should be:

X X X X
X X X X
X X X X
X O X X
*/
/*
bfs, 经典题目， 在第三个for里面有错误， 原来是用了两个if ， 但是如果这样写的话， 第二个if肯定执行， 然后把第一个if中的‘o’替换掉
*/
class myPoint{
public:
    int x;
    int y;
    myPoint(int a, int b){x = a; y = b;}
};

class Solution {
public:
    void bfsCheck(vector<vector<char>>& board, const int x, const int y){
        board[x][y] = 'Y';
        queue<myPoint> q;
        q.push(myPoint(x, y));
        while(!q.empty()){
            myPoint p = q.front();
            q.pop();
            int i = p.x;
            int j = p.y;
            if(i - 1 >=0 && board[i - 1][j] == 'O'){
                board[i - 1][j] = 'Y';
                q.push(myPoint(i - 1, j));
            }
            //right
            if(i + 1 < board.size() && board[i + 1][j] == 'O'){
                board[i + 1][j] = 'Y';
                q.push(myPoint(i + 1, j));
            }
            //Up
            if(j - 1 >= 0 && board[i][j - 1] == 'O'){
                board[i][j - 1] = 'Y';
                q.push(myPoint(i, j - 1));
            }
            if(j + 1 < board[0].size() && board[i][j + 1] == 'O'){
                board[i][j + 1] = 'Y';
                q.push(myPoint(i, j + 1));
            }
        }
    }
    void solve(vector<vector<char>> &board) {
        if(board.size() == 0) return;
        for(int i = 0; i < board.size(); i++){
            if(board[i][0] == 'O') bfsCheck(board, i, 0);
            if(board[i][board[0].size() - 1] == 'O') bfsCheck(board, i, board[0].size() - 1);
        }
        for(int j = 0; j < board[0].size(); j++){
            if(board[0][j] == 'O') bfsCheck(board, 0, j);
            if(board[board.size() - 1][j] == 'O') bfsCheck(board, board.size() - 1, j);
        }
        for(int i = 0; i < board.size(); i++){
            for(int j = 0; j < board[0].size(); j++){
                if(board[i][j] == 'Y'){
                    board[i][j] = 'O';
                }else if(board[i][j] == 'O'){
                    board[i][j] = 'X';
                }
            }
        }
        return;
    }
};

