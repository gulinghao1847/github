/*Palindrome Partitioning Total Accepted: 8204 Total Submissions: 32313 My Submissions
Given a string s, partition s such that every substring of the partition is a palindrome.

Return all possible palindrome partitioning of s.

For example, given s = "aab",
Return

  [
    ["aa","b"],
    ["a","a","b"]
  ]
*/
/*
back_tracing + 2D DP
*/
class Solution {
public:
	/*
	From top to bot dp
	*/
    bool isPalindrome(vector<vector<int>>& matrix, int i, int j, string& s){
        if(matrix[i][j] == 1) return true;
        if(matrix[i][j] == 2) return false;
        if(j - i < 2 && s[i] == s[j]){
            matrix[i][j] = 1;
            return true;
        }
        if(j - i >= 2 && s[i] == s[j] && isPalindrome(matrix, i + 1, j - 1, s)){
            matrix[i][j] = 1;
            return true;
        }
        matrix[i][j] = 2;
        return false;
    }
    
	//back_tracing part
    void partitionHelper(vector<vector<string>>& result, vector<string>& now, vector<vector<int>>& matrix, int pos, string& s){
        if(pos == s.size()){
            result.push_back(now);
            return;
        }
        
        for(int i = pos; i < s.size(); i++){
            if(isPalindrome(matrix, pos, i, s)){
                now.push_back(s.substr(pos, i - pos + 1));
                partitionHelper(result, now, matrix, i + 1, s);
                now.pop_back();
            }
        }
    }
    
	//main function
    vector<vector<string>> partition(string s) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        vector<vector<string>> result;
        vector<string> now;
        vector<vector<int>> matrix(s.size(), vector<int>(s.size(), 0));
        partitionHelper(result, now, matrix, 0, s);
        return result;
    }
};

