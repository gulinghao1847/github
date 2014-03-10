/*Sudoku Solver Total Accepted: 4204 Total Submissions: 20920 My Submissions
Write a program to solve a Sudoku puzzle by filling the empty cells.

Empty cells are indicated by the character '.'.

You may assume that there will be only one unique solution.


A sudoku puzzle...

*/
/*
classic back_tracing problem

*/
class Solution {
public:
    void getNext(int row, int column, int& nextR, int& nextC, int size){
        if(column == size){
            nextR = row + 1;
            nextC = 0;
        }else{
            nextR = row;
            nextC = column + 1;
        }
    }
    
    bool valid(vector<vector<char>>& board, int row, int column){
        for(int i = 0; i < board.size(); i++){
            if((i != row && board[i][column] == board[row][column]) || (i != column && board[row][i] == board[row][column])){
                return false;
            }
        }
        int a = (row/3) * 3;
        int b = (column/3) * 3;
        for(int i = a; i < a + 3; i++){
            for(int j = b; j < b + 3; j++){
                if(!(i == row && j == column) && board[i][j] == board[row][column]){
                    return false;
                }
            }
        }
        return true;
    }
    
    bool validSudoku(vector<vector<char>>& board, int row, int column){
        //end condition
        if(row == board.size() && column == 0){
            return true;
        }
        //check if it is filled
        int nextRow, nextColumn;
        getNext(row, column, nextRow, nextColumn, board.size());
        if(board[row][column] == '.'){
            for(int i = 0; i < 9; i++){
                board[row][column] = '1' + i;
                if(valid(board, row, column)){
                    if(validSudoku(board, nextRow, nextColumn)){
                        return true;
                    }
                }
                board[row][column] = '.';
            }
        }else if(validSudoku(board, nextRow, nextColumn)){
            return true;
        }
        return false;
    }
    void solveSudoku(vector<vector<char> > &board) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        validSudoku(board, 0, 0);
    }
};

