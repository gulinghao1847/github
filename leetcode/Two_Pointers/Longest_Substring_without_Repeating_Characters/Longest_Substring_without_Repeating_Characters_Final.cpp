/*
Longest Substring Without Repeating Characters Total Accepted: 7062 Total Submissions: 30790 My Submissions
Given a string, find the length of the longest substring without repeating characters. For example,
 the longest substring without repeating letters for "abcabcbb" is "abc", which the length is 3. For "bbbbb" the longest substring is "b", with the length of 1.
*/
/*
对于本题， 注意两种情况， string = "avca" string = "bcdafsa";
*/

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        int* appear = new int[256];
        int start = 0;
        int size = s.size();
        int longest = 0;
        
        for(int i = 0; i < 256; i++) appear[i] = 0;
        
        for(int i = 0; i < size; i++){
            if(appear[s[i]] == 0){
                appear[s[i]] ++;
            }else if(appear[s[i]] == 1){
                appear[s[i]] ++;
                while(appear[s[start]] != 2){
                    appear[s[start]]--;
                    start++;
                }
                start++;
                appear[s[i]]--;
            }
            
            if(longest < (i - start + 1)){
                longest = i -start + 1;
            }
        }
        return longest;
    }
};

/*
version 2
*/
/*
本题目用的是hashmap 然后每次更新start 从而求出最大的
*/
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int start = 0;
        int len = 0;
        int maxLen = 0;
        int hashmap[256];
        for(int i = 0; i < 256; i++) hashmap[i] = 0;
        for(int i = 0; i < s.size(); i++){
            if(hashmap[s[i]] == 0){
                hashmap[s[i]]++;
                //len++;
            }else{
                int len = i - start;
                maxLen = max(maxLen, len);
                hashmap[s[i]]++;
                //len++;
                while(hashmap[s[start]] == 1){
                    hashmap[s[start]]--;
                    start++;
                    //len--;
                }
                hashmap[s[start]]--;
                start++;
            }
        }
        len = s.size() -start;
        maxLen = max(maxLen, len);
        return maxLen;
    }
};

//第二种情况，  一开始没有加入71-72行， 总是报错， 和第一种情况每次for循环都对max更新不一样， 第二种情况只对发生了重复的时候进行更新， 因此有可能了最后不会产生重复， 但是最后一个却是最大的例子：string ＝ “qopubjguxhxdipfzwswybgfylqvjzhar”