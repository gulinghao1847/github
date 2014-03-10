/*
Substring with Concatenation of All Words Total Accepted: 3966 Total Submissions: 23015 My Submissions
You are given a string, S, and a list of words, L, that are all of the same length. Find all starting indices of substring(s) in S that is a concatenation of each word in L exactly once and without any intervening characters.

For example, given:
S: "barfoothefoobarman"
L: ["foo", "bar"]

You should return the indices: [0,9].
(order does not matter).
*/
class Solution {
public:
    vector<int> findSubstring(string S, vector<string> &L) {
        map<string, int> mp;
        vector<int> res;
        if(L.size() == 0) return res;
        for(int i = 0; i < L.size(); i++){
            mp[L[i]]++;
        }
        int length = S.size() - L.size() * L[0].size();
        int len = L[0].size();
        map<string, int> check;
        for(int i = 0; i <= length; i++){
            int count = 0;
            int iter = i;
            string word = S.substr(iter, len);
            while(iter + len <= S.size() && mp.find(word) != mp.end() && check[word] != mp[word] && count != L.size()){
                count++;
                check[word]++;
                iter = iter + len;
                word = S.substr(iter, len);
            }
            if(count == L.size()){
                res.push_back(i);
            }
            check.clear();
        }
        return res;
    }
};