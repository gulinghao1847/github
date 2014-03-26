/*
Longest Valid Parentheses Total Accepted: 5843 Total Submissions: 31467 My Submissions
Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.

For "(()", the longest valid parentheses substring is "()", which has length = 2.

Another example is ")()())", where the longest valid parentheses substring is "()()", which has length = 4.
*/
class Solution {
public:
    int longestValidParentheses(string s) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        stack<int> q;
        int size = s.size();
        int last = -1;
        int max = 0;
        for(int i = 0; i < size; i++){
            if(s[i] == '('){
                q.push(i);
            }else{
                if(q.empty()){
                    last = i;   
                }else{
                    q.pop();
                    if(q.empty()){
                        max = max>(i - last)?max:(i - last);
                    }else{
                        max = max>(i - q.top())?max:(i - q.top());                   
                    }
                }
            }
        }
        return max;
    }
};
