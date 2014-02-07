class Solution {
public:
    string longestPalindrome(string s) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        int size = s.size();
        int maxLen = 0;
        int maxStart = -1;
        vector<vector<bool>> palin(size, vector<bool>(size, false));
        for(int i = size - 1; i >= 0; i -- ){
            for(int j = i; j < size; j++){
                if(s[i] == s[j] &&(j - i < 2 || palin[i + 1][j - 1])){
                    palin[i][j] = true;
                    if((j - i + 1) > maxLen){
                        maxLen = j - i + 1;
                        maxStart = i;
                    }
                }
            }
        }
        return s.substr(maxStart, maxLen);
    }
};