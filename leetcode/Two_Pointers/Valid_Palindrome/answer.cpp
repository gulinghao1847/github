/*
Valid Palindrome Total Accepted: 9173 Total Submissions: 42252 My Submissions
Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.

For example,
"A man, a plan, a canal: Panama" is a palindrome.
"race a car" is not a palindrome.

Note:
Have you consider that the string might be empty? This is a good question to ask during an interview.

For the purpose of this problem, we define empty string as valid palindrome.
*/
class Solution {
public:
    bool valid(char a){
        return (a <= 'Z' && a >= 'A') || (a <= 'z' && a >= 'a') || (a <= '9' && a >= '0');
    }
    
    bool equalChar(char a, char b){
        if(a <= '9' && a >= '0'){
            return a == b;
        }
        return a == b || (a + 32) == b || a == (b + 32);
    }
    
    bool isPalindrome(string s) {
        int begin = 0;
        int end = s.size() - 1;
        while(begin < end){
            while(begin < s.size() && !valid(s[begin])) begin++;
            while(end >= 0 && !valid(s[end])) end--;
            if(begin <= end){
                if(!equalChar(s[begin], s[end])){
                    return false;
                }
            }
            begin++;
            end--;
        }
        return true;
    }
};

/*
In ASCII Table : 'A' = 'a' + 32 not 'a' + 26!!!!! line 24
31 和32 行要加上 判断， 不然会out of bound
*/
