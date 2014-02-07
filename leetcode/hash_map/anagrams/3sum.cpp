/**
Anagrams Total Accepted: 1241 Total Submissions: 5492 My Submissions
Given an array of strings, return all groups of strings that are anagrams.

Note: All inputs will be in lower-case.
*/
/*
hash_map 的典型应用
*/
class Solution {
public:
    vector<string> anagrams(vector<string> &strs) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        map<string, vector<string>> mp;
        vector<string> res;
        vector<string>::iterator it;
        for(it = strs.begin(); it != strs.end(); it++){
            string s = *it;
            sort(s.begin(), s.end());
            mp[s].push_back(*it);
        }
		
        map<string, vector<string>>::iterator iter;
        for(iter = mp.begin(); iter != mp.end(); iter++){
            if(iter -> second.size() > 1){
                for(it = iter -> second.begin(); it != iter -> second.end(); it++){
                    res.push_back(*it);
                }
            }
        }
        return res;
    }
};