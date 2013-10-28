/*
PURELY USING BACK_TRACING, TAKE LESS SPACE, BUT TAKE MORE TIME
*/
class Solution {
public:
    void run(string& s, unordered_set<string>& dict, int begin, vector<string>& result, string& now){
        int size = s.size();
        unordered_set<string>::iterator it;
        if(begin == size){
            result.push_back(now);
            return;
        }
        
        for(int i = begin; i < size; i++){
            it = dict.find(s.substr(begin, i - begin + 1));
            if(it == dict.end()) continue;
            int len = now.size();
            if(len != 0) now = now + " ";
            now = now + s.substr(begin, i - begin + 1);
            run(s, dict, i + 1, result, now);
            now.erase(len, i - begin + 2);
        }
    }
    vector<string> wordBreak(string s, unordered_set<string> &dict) {
        // Note: The Solution object is instantiated only once and is reused by each test case
        vector<string> result;
        string now;
        run(s, dict, 0, result, now);
        return result;
    }
};