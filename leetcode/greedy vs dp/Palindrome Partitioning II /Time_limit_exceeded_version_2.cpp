class Solution {
public:
    bool check(string& s, int b, int e, vector<vector<bool>>& p){
        //int size = s.size();
        int begin = b;
        int end = e;
        while(begin <= end){
            if(p[begin][end] == true) return true;
            if(s[begin] != s[end]){
                p[b][e] = false;
                return false;
            }
            begin++;
            end--;
        }
        p[b][e] = true;
        return true;
    }
    int run(string& s, int begin, int end, vector<int>& m, vector<vector<bool>>& p){
        int min = INT_MAX;
        int temp = 0;
        if(m[begin] != INT_MAX){
            return m[begin];
        }
        
        for(int i = begin; i < end; i++){
            if(check(s, begin, i, p)){
                temp = run(s, i + 1, end, m, p);
                min = (min < temp ? min : temp) + 1;
            }
        }
        m[begin] = min;
        return min;
    }
    int minCut(string s) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        int size = s.size();
        if(!size) return 0;
        vector<int> m(size + 1, INT_MAX);
        vector<vector<bool>> palin(size, vector<bool>(size, false));
        
        for(int i = 0; i < size; i++) palin[i][i] = true;
        
        m[size] = -1;
        run(s, 0, size - 1, m, palin);
        return m[0];
    }
};