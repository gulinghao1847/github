/*
Distinct Subsequences Total Accepted: 5015 Total Submissions: 21339 My Submissions
Given a string S and a string T, count the number of distinct subsequences of T in S.

A subsequence of a string is a new string which is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (ie, "ACE" is a subsequence of "ABCDE" while "AEC" is not).

Here is an example:
S = "rabbbit", T = "rabbit"

Return 3.
*/
class Solution {
public:
    int numDistinct(string S, string T) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        vector<vector<int>> match(T.size() + 1, vector<int>(S.size() + 1, 0));
        match[0][0] = 1;
        if(S.size() < T.size()) return 0;
        for(int i = 1; i <= T.size(); i++){
            for(int j = 1; j <= S.size(); j++){
                match[0][j] = 1;
                if(T[i - 1] == S[j - 1]){
                    match[i][j] = match[i - 1][j - 1] + match[i][j - 1];
                }else{
                    match[i][j] = match[i][j - 1];
                }
            }
        }
        return match[T.size()][S.size()];
    }
};

