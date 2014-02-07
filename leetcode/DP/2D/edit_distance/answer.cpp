/*
Edit Distance Total Accepted: 4159 Total Submissions: 17080 My Submissions
Given two words word1 and word2, find the minimum number of steps required to convert word1 to word2. (each operation is counted as 1 step.)

You have the following 3 operations permitted on a word:

a) Insert a character
b) Delete a character
c) Replace a character
*/
class Solution {
public:
    int minDistance(string word1, string word2) {
        int s1 = word1.size();
        int s2 = word2.size();
        vector<vector<int>> match(s1 + 1, vector<int>(s2 + 1, 0));
        for(int i = 0; i <= s1; i++) match[i][0] = i;
        for(int i = 0; i <= s2; i++) match[0][i] = i;
        for(int i = 1; i <= s1; i++){
            for(int j = 1; j <= s2; j++){
                int cost = 0;
                if(word1[i - 1] == word2[j - 1]){
                    cost = match[i - 1][j - 1];
                }else{
                    cost = match[i - 1][j - 1] + 1;
                }
                cost = min(min(match[i - 1][j], match[i][j - 1]) + 1, cost);
                match[i][j] = cost;
            }
        }
        return match[s1][s2];
    }
};

