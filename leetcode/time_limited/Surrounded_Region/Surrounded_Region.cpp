class Solution {
public:
    bool doDFS(vector<vector<char>>& board, int row, int column, vector<vector<bool>>& v){
        if(row >= board.size() || row<0 || column<0 || column >= board[0].size()){
                return false;
        }
        if(v[row][column] == true || board[row][column] == 'X'){
            return true;
        }
        v[row][column] = true;
        if(board[row][column] == 'O'&&doDFS(board,row + 1, column, v)&&doDFS(board,row - 1, column, v)&&doDFS(board,row, column + 1, v)&&doDFS(board,row, column - 1, v)){
            v[row][column] = false;
            board[row][column] = 'X';
            return true;
        }
        v[row][column] = false;
        return false;
    }
    
    void solve(vector<vector<char>> &board) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        int s1 = board.size();
        if(s1 == 0){
            return;
        }
        int s2 = board[0].size();
        vector<vector<bool>> visited(s1, vector<bool>(s2, false));
        for(int i = 0; i < s1; i++){
            for(int j = 0; j < s2; j++){
                if(board[i][j] == 'O'){
                    doDFS(board, i, j, visited);
                }
            }
        }
        return;
    }
};