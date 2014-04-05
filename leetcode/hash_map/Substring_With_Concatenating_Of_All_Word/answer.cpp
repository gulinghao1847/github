/*
Substring with Concatenation of All Words Total Accepted: 3966 Total Submissions: 23015 My Submissions
You are given a string, S, and a list of words, L, that are all of the same length. Find all starting indices of substring(s) in S that is a concatenation of each word in L exactly once and without any intervening characters.

For example, given:
S: "barfoothefoobarman"
L: ["foo", "bar"]

You should return the indices: [0,9].
(order does not matter).
*/
/*
wrong
if L contains duplicate, this program doesn't work
*/
class Solution {
public:
    vector<int> findSubstring(string S, vector<string> &L) {
        unordered_map<string, int> mp;
        vector<int> result;
        if(L.size() == 0 || L[0].size() == 0) return result;
        for(int i = 0; i < L.size(); i++){
            mp[L[i]] = i;
        }
        int sizeOfWord = L[0].size();
        int size = S.size() - sizeOfWord * L.size();
        for(int i = 0; i <= size; i++){
            if(mp.find(S.substr(i, sizeOfWord)) != mp.end()){
                vector<bool> appear(L.size(), false);
                int iter = i;
                int count = 0;
                string now = S.substr(iter, sizeOfWord);
                while(mp.find(now) != mp.end() && appear[mp[now]] == false){
                    appear[mp[now]] = true;
                    count++;
                    iter = iter + sizeOfWord;
                    if(count == L.size()){
                        result.push_back(i);
                        break;
                    }
                    now = S.substr(iter, sizeOfWord);
                }
            }
        }
        return result;
    }
};

/*
right
*/
class Solution {
public:
    vector<int> findSubstring(string S, vector<string> &L) {
        unordered_map<string, int> mp;
        vector<int> result;
        if(L.size() == 0 || L[0].size() == 0) return result;
        for(int i = 0; i < L.size(); i++){
            mp[L[i]]++;
        }
        int sizeOfWord = L[0].size();
        int size = S.size() - sizeOfWord * L.size();
        for(int i = 0; i <= size; i++){
            if(mp.find(S.substr(i, sizeOfWord)) != mp.end()){
                unordered_map<string, int> myMp(mp);
                int iter = i;
                int count = 0;
                string now = S.substr(iter, sizeOfWord);
                while(mp.find(now) != mp.end() && myMp[now] != 0){
                    myMp[now]--;
                    //appear[mp[now]] = true;
                    count++;
                    iter = iter + sizeOfWord;
                    if(count == L.size()){
                        result.push_back(i);
                        break;
                    }
                    now = S.substr(iter, sizeOfWord);
                }
            }
        }
        return result;
    }
};