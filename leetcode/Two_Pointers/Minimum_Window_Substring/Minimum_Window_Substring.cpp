class Solution {
public:
    string minWindow(string S, string T) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        int s1 = S.size();
        int s2 = T.size();
        int* appear = new int[256];
        int* expect = new int[256];
        int app = 0;
        int start = 0;
        int min = INT_MAX;
        int min_begin = 0;
        for(int i = 0; i < 256; i++) {appear[i] = 0; expect[i] = 0;}
        
        for(int i = 0; i < s2; i++) expect[T[i]]++;
        
        for(int i = 0; i < s1; i++){
            if(expect[S[i]] == 0){
                continue;
            }
            
            appear[S[i]]++;
            if(appear[S[i]] <= expect[S[i]]) app++;
            
            if(app == s2){
                while(expect[S[start]] == 0 || appear[S[start]] > expect[S[start]]){
                    appear[S[start]]--;
                    start++;
                }
                if(min > i - start + 1){
                    min = i - start + 1;
                    min_begin = start;
                }
            }
        }
        if(min == INT_MAX){
            return "";
        }
        return S.substr(min_begin,min);
    }
};