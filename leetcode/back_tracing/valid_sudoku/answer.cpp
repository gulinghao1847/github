/*Valid Sudoku Total Accepted: 4862 Total Submissions: 17990 My Submissions
Determine if a Sudoku is valid, according to: Sudoku Puzzles - The Rules.

The Sudoku board could be partially filled, where empty cells are filled with the character '.'.


A partially filled sudoku which is valid.

Note:
A valid Sudoku board (partially filled) is not necessarily solvable. Only the filled cells need to be validated.
*/
class Solution {
public:
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
    bool isValidSudoku(vector<vector<char> > &board) {
        for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++){
                if(board[i][j] != '.' && !valid(board, i, j)){
                    return false;
                }
            }
        }
        return true;
    }
};
/*
这道题目要和valid sudoku whether or not it has a solution不同， 这题目只要验证给定的就可以了， 不需要其他的东西， 在验证的时候也要注意， 本道我用的笨方法， 实际上可以用一个int[10]来做就可以了， 速度快很多
这题目还要注意的， 我在验证是否有元素和本元素相同的时候， 因为用的是for loop， 所以一定要把自己给忽略了， 不然肯定是false

*/

