/*

Implement strStr() Total Accepted: 5346 Total Submissions: 26470 My Submissions
Implement strStr().

Returns a pointer to the first occurrence of needle in haystack, or null if needle is not part of haystack.
*/
class Solution {
public:
    char *strStr(char *haystack, char *needle) {
        int s1 = 0;
        int s2 = 0;
        while(haystack[s1] != '\0') s1++;
        while(needle[s2] != '\0') s2++;
        if(s1 == 0 && s2 == 0) return needle;
        if(s2 == 0) return haystack;
        for(int i = 0; i < s1 - s2 + 1; i++){
            if(haystack[i] == needle[0]){
               int count = 0;
               while(haystack[i + count] == needle[count]){
                   count++;
                   if(count == s2){
                       return &haystack[i];
                   }
               }
            }
        }
        return NULL;
    }
};
