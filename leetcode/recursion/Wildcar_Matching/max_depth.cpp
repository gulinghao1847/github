/*
Wildcard Matching Total Accepted: 857 Total Submissions: 8144 My Submissions
Implement wildcard pattern matching with support for '?' and '*'.

'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).

The matching should cover the entire input string (not partial).

The function prototype should be:
bool isMatch(const char *s, const char *p)

Some examples:
isMatch("aa","a") → false
isMatch("aa","aa") → true
isMatch("aaa","aa") → false
isMatch("aa", "*") → true
isMatch("aa", "a*") → true
isMatch("ab", "?*") → true
isMatch("aab", "c*a*b") → false
*/
class Solution {
public:
    bool isMatch(const char *s, const char *p) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        const char* str = s;
        const char* pat = p;
        const char* strPos = NULL;
        const char* patPos = NULL;
        int star = 0;
        while(*str != '\0'){
            switch(*pat){
                case '?': str++;
                          pat++;
                          break;
                case '*': while(*pat == '*') pat++;
                          strPos = str;
                          patPos = pat;
                          star = 1;
                          break;
                default:  if(*str == *pat){
                              str++;
                              pat++;
                              break;
                          }
                          if(star == 0) return false;
                          pat = patPos;
                          str = strPos + 1;
                          strPos = str;
                          break;
            }
        }
        while(*pat == '*') pat++;
        return (*pat == '\0');
    }
};
