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
/*
在traversal 图的时候， 要注意mark visited的问题， 什么时候mark？
是上一个节点在traversal的时候就要mark， 不然两个node 同时都和这个node 连接， 就会push n次造成死循环， 所以就要在上一个节点上mark！！！
mark 的方式：
1.创建一个一摸一样的graph（bool value）
2.在现有的图上表示
3. 单独创立数据建构重新作图。
*/
class myPoint{
public:
    int x;
    int y;
    myPoint(int x, int y){
        this -> x = x;
        this -> y = y;
    }
};

class Solution {
public:
    bool check(vector<vector<char>> &board, int i, int j){
        return i >= 0 && i < board.size() && j >= 0 && j < board[0].size();
    }
    void dfsTraversal(vector<vector<char>> &board, int i, int j){
        if(board[i][j] != 'O') return;
        board[i][j] = 'Y';
        queue<myPoint> q;
        q.push(myPoint(i, j));
        while(!q.empty()){
            int x = q.front().x;
            int y = q.front().y;
            q.pop();
            if(check(board, x - 1, y) && board[x - 1][y] == 'O'){
                 board[x - 1][y] = 'Y';
                q.push(myPoint(x - 1, y));
            }
            if(check(board, x + 1, y) && board[x + 1][y] == 'O'){
                 board[x + 1][y] = 'Y';
                q.push(myPoint(x + 1, y));
            }
            if(check(board, x, y + 1) && board[x][y + 1] == 'O'){
                 board[x][y + 1] = 'Y';
                q.push(myPoint(x, y + 1));
            }
            if(check(board, x, y - 1) && board[x][y - 1] == 'O'){
                 board[x][y - 1] = 'Y';
                q.push(myPoint(x, y - 1));
            }
        }
    }
    void solve(vector<vector<char>> &board) {
        if(board.size() == 0 || board[0].size() == 0) return;
        
        for(int i = 0; i < board.size(); i++){
            dfsTraversal(board, i, 0);
            dfsTraversal(board, i, board[0].size() - 1);
        }
        
        for(int i = 0; i < board[0].size(); i++){
            dfsTraversal(board, 0, i);
            dfsTraversal(board, board.size() - 1, i);
        }
        
        for(int i = 0; i < board.size(); i++){
            for(int j = 0; j < board[0].size(); j++){
                if(board[i][j] == 'O'){
                    board[i][j] = 'X';
                }else if(board[i][j] == 'Y'){
                    board[i][j] = 'O';
                }
            }
        }
    }
};

