class Solution {
public:
    vector<int> findSubstring(string S, vector<string> &L) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        int s1 = S.size();
        int s2 = L.size();
        vector<int> result;
        if(!s1 || !s2){
            return result;
        }
        
        int s3 = L[0].size();
        //get a dict so that the cost of find is O(1)
        map<string, int> dict;
        for(int i = 0; i < s2; i++){
            dict[L[i]]++;
        }
        map<string,int> mp;
        for(int i = 0; i < s1 - (s2*s3) + 1; i++){
            mp.clear();
            map<string,int>::iterator it;
            int start = i;
            int num = 0;
            while(start + s3 <= s1){
                string s = S.substr(start, s3);
                it = mp.find(s);
                //it2 = added.find(S.substr(start, s3));
                if(it == dict.end()){
                    break;
                }
                if(mp[s] >= dict[s]){
                    break;
                }
                mp[s]++;
                num++;
                //added.insert(s);
                start = start + s3;
                if(num == s2){
                    result.push_back(i);
                    break;
                }
            }
        }
        return result;
    }
};