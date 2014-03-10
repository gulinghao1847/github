/*
Generate Parentheses Total Accepted: 7480 Total Submissions: 24670 My Submissions
Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

For example, given n = 3, a solution set is:

"((()))", "(()())", "(())()", "()(())", "()()()"
*/
class Solution {
public:
    void run(vector<string>& result, string& now, int leftRemaining, int rightRemaining){
        //end condition
        if(leftRemaining == 0 && rightRemaining == 0){
            result.push_back(now);
            return;
        }
        if(leftRemaining){
            now.push_back('(');
            run(result,now,leftRemaining - 1, rightRemaining + 1);
            now.pop_back();
        }
        if(rightRemaining){
            now.push_back(')');
            run(result, now, leftRemaining, rightRemaining - 1);
            now.pop_back();
        }
    }
    vector<string> generateParenthesis(int n) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        vector<string> result;
        string now;
        run(result, now, n, 0);
        return result;
    }
};

