/**
Word Break II Total Accepted: 1213 Total Submissions: 10226 My Submissions
Given a string s and a dictionary of words dict, add spaces in s to construct a sentence where each word is a valid dictionary word.

Return all such possible sentences.

For example, given
s = "catsanddog",
dict = ["cat", "cats", "and", "sand", "dog"].

A solution is ["cats and dog", "cat sand dog"].
 */
/*
I think this solution should be the fastest , but it takes more sapce
*/
class Solution {
public:
    bool isInDict(vector<vector<int>>& inDict, int a, int b, unordered_set<string>& dict, string& s){
        if(a > b) return true;
        if(inDict[a][b] == 1) return true;
        if(inDict[a][b] == 2) return false;
        unordered_set<string>::iterator it;
        it = dict.find(s.substr(a, b - a + 1));
        
        if(it != dict.end()){
            inDict[a][b] = 1;
            return true;
        }
        
        for(int i = a; i < b; i++){
            if(isInDict(inDict, a, i, dict, s) && isInDict(inDict, i + 1, b, dict, s)){
                inDict[a][b] = 1;
                return true;
            }
        }
        inDict[a][b] = 2;
        return false;
    }
    
    void run(string& s, unordered_set<string>& dict, int begin, vector<string>& result, string& now, vector<vector<int>>& inDict){
        int size = s.size();
        if(begin == size){
            result.push_back(now);
            return;
        }
        
        for(int i = begin; i < size; i++){
            /*
            it = dict.find(s.substr(begin, i - begin + 1));
            if(it == dict.end()) continue;
            */
            if(isInDict(inDict, begin, i, dict, s) && isInDict(inDict, i + 1, size - 1, dict, s)){
                int len = now.size();
                if(len != 0) now = now + " ";
                now = now + s.substr(begin, i - begin + 1);
                run(s, dict, i + 1, result, now, inDict);
                now.erase(len, i - begin + 2);
            }
        }
    }
	
    vector<string> wordBreak(string s, unordered_set<string> &dict) {
        // Note: The Solution object is instantiated only once and is reused by each test case
        vector<string> result;
        int size = s.size();
        string now;
        vector<vector<int>> inDict(size, vector<int>(size, 0));
        run(s, dict, 0, result, now, inDict);
        return result;
    }
};