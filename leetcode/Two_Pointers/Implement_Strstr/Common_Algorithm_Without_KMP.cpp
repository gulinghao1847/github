class Solution {
public:
    char *strStr(char *haystack, char *needle) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        int iter = 0;
        int s2 = 0;
        int s1 = 0;
        int len = 0;
        for(int i = 0; needle[i] != '\0'; i++) s2++;
        for(int i = 0; haystack[i] != '\0'; i++) s1++;
        if(s1 == 0 && s2 == 0) return needle;
        if(s2 == 0) return haystack;
        while(iter + s2 - 1 < s1){
            len = 0;
            int now = iter;
            for(int i = 0; i < s2 ; i++){
                if(haystack[now] != needle[i]) break;
                now++;
                len++;
                if(len == s2){
                    return &haystack[iter];
                }
            }
            iter++;
        }
        return NULL;
    }
};