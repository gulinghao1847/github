/**
Valid Palindrome Total Accepted: 1911 Total Submissions: 9196 My Submissions
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
    bool isPalindrome(string s) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        for(int i = 0; i < s.size(); i++){
            if(s[i] <= 'Z' && s[i] >= 'A') s[i] += 'a' - 'A';
            if(!((s[i] <= 'z' && s[i] >= 'a') || (s[i] >= '0' && s[i] <= '9'))) {s.erase(i,1);i--;}
        }
        int size = s.size();
        int begin = 0;
        int end = size - 1;
        while(begin <= end){
            if(s[begin++] == s[end--]) continue;
            else return false;
        }
        return true;  
    }
};
/*
本题目要注意的就是在line：20, 每次erase 之后记得要i－－；
*/