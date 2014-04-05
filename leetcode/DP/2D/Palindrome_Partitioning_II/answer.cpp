/*
Palindrome Partitioning II Total Accepted: 6637 Total Submissions: 38258 My Submissions
Given a string s, partition s such that every substring of the partition is a palindrome.

Return the minimum cuts needed for a palindrome partitioning of s.

For example, given s = "aab",
Return 1 since the palindrome partitioning ["aa","b"] could be produced using 1 cut.
*/
/*
Two dp
1.find if the string s.substr(i, j - i + 1) is parlindrome
2.find the min cut
*/
class Solution {
public:
    int minCut(string s) {
        int size = s.size();
        vector<vector<bool>> palin(size, vector<bool>(size, false));
		
		//first dp
        for(int i = size - 1; i >= 0; i--){
            for(int j = i; j <= size - 1; j++){
                if(s[i] == s[j] && (j - i < 2 || palin[i + 1][j - 1])){
                    palin[i][j] = true;
                }
            }
        }
        vector<int> matrix(s.size() + 1, INT_MAX);
        matrix[s.size()] = -1;
		//second dp
        for(int i = s.size() - 1; i >= 0; i--){
            for(int j = i + 1; j <= s.size(); j++){
                if(palin[i][j - 1]){
                    matrix[i] = min(matrix[i], matrix[j] + 1);
                }
            }
        }
        return matrix[0];
    }
};

