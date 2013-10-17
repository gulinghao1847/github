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