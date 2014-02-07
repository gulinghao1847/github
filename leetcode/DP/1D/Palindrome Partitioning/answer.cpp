/*
Palindrome Partitioning Total Accepted: 4604 Total Submissions: 18825 My Submissions
Given a string s, partition s such that every substring of the partition is a palindrome.

Return all possible palindrome partitioning of s.

For example, given s = "aab",
Return

  [
    ["aa","b"],
    ["a","a","b"]
  ]
Discuss


*/
class Solution {
public:
    bool isPalin(vector<vector<int>>& palin, int a, int b, string& s){
        if(a > b) return true;
        if(palin[a][b] == 1) return true;
        if(palin[a][b] == 2) return false;
        if(b - a < 2){
            palin[a][b] = (s[a] == s[b]) ? 1 : 2;
        }else if(s[a] == s[b] && isPalin(palin, a + 1, b - 1, s)){
            palin[a][b] = 1;
        }else
            palin[a][b] = 2;
        return palin[a][b] == 1 ? true : false;
    }
    void run(vector<vector<string>>& result, vector<string>& now, string& s, int begin, vector<vector<int>>& palin){
        int size = s.size();
        if(begin == size){
            result.push_back(now);
            return;
        }
        for(int i = begin; i < size; i++){
            if(isPalin(palin, begin + 0, i + 0, s)/* && isPalin(palin, i + 1, size - 1, s)*/){
                now.push_back(s.substr(begin, i - begin + 1));
                run(result, now, s, i + 1, palin);
                now.pop_back();
            }
        }
    }
    vector<vector<string>> partition(string s) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        int size = s.size();
        vector<vector<string>> result;
        vector<string> now;
        vector<vector<int>> palin(size, vector<int>(size, 0));
        run(result, now, s, 0, palin);
        return result;
    }
};

