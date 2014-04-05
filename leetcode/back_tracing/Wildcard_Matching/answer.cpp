/*
Wildcard Matching Total Accepted: 5646 Total Submissions: 44386 My Submissions
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

/*
recusion
*/
class Solution {
public:
    bool isMatch(const char *s, const char *p) {
        if(*s == '\0') return *p == '\0';
        if(*p == '*'){
            while(*s != '\0'){
                if(isMatch(s, p + 1)){
                    return true;
                }
                s++;
            }
            return *(p + 1) == '\0';
        }else if(*p == '?'){
            return *s != '\0' && isMatch(s + 1, p + 1);
        }
        return *s == *p && isMatch(s + 1, p + 1);
    }
};
/*
iteration
*/
class Solution {
public:
    bool isMatch(const char *s, const char *p) {
        const char* sPos = NULL;
        const char* pPos = NULL;
        bool star = false;
        while(*s != '\0'){
            if(*p == '?'){
                s++;
                p++;
            }else if(*p == '*'){
                p++;
                if(*p == '\0') return true;
                sPos = s;
                pPos = p;
                star = true;
            }else{
                if(*s == *p){
                    s++;
                    p++;
                    continue;
                }
                if(!star) return false;
                s = sPos++;
                p = pPos;
            }
        }
        while(*p == '*') p++;
        return *p == '\0';
    }
};

