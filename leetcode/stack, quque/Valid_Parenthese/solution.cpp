/**
Valid Parentheses Total Accepted: 1681 Total Submissions: 6033 My Submissions
Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

The brackets must close in the correct order, "()" and "()[]{}" are all valid but "(]" and "([)]" are not.
 */
/*
Time: O(N), Space: O(N);
*/
class Solution {
public:
    bool isValid(string s) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        stack<char> q;
        int size = s.size();
        for(int i = 0; i < size; i++){
            if(s[i] == '(' || s[i] == '{' || s[i] == '['){
                q.push(s[i]);
            }
            else if(!q.empty()){
                char left= q.top();
                q.pop();
                char& right = s[i];
                switch(s[i]){
                    case ')':
                        if(left != '(') return false;
                        break;
                    case ']':
                        if(left != '[') return false;
                        break;
                    case '}':
                        if(left != '{') return false;
                        break;
                    default:
                        return false;
                }
            }else{ 
                return false;
            }
        }
        return q.empty()?true:false;
    }
};