/*

Length of Last Word Total Accepted: 5117 Total Submissions: 18738 My Submissions
Given a string s consists of upper/lower-case alphabets and empty space characters ' ', return the length of last word in the string.

If the last word does not exist, return 0.

Note: A word is defined as a character sequence consists of non-space characters only.

For example, 
Given s = "Hello World",
return 5.
*/
class Solution {
public:
    int lengthOfLastWord(const char *s) {
        if(s == NULL) return 0;
        int len = 0;
        int cur = 0;
        int ret = 0;
        while(s[cur] != '\0'){
            if(s[cur] == ' '){
                ret = len;
                len = 0;
                while(s[cur] == ' ') cur++;
            }else{
                len++;
                cur++;
            }
        }
        if(len != 0){
            ret = len;
        }
        return ret;
    }
};

