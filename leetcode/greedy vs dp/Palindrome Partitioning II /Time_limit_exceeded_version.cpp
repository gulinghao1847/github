class Solution {
public:
    bool check(string& s, int b, int e){
        //int size = s.size();
        int begin = b;
        int end = e;
        while(begin <= end){
            if(s[begin] != s[end]){
                return false;
            }
            begin++;
            end--;
        }
        return true;
    }
    int run(string& s, int begin, int end, vector<int>& m){
        int min = INT_MAX;
        int temp = 0;
        if(m[begin] != INT_MAX){
            return m[begin];
        }
        
        for(int i = begin; i < end; i++){
            if(check(s, begin, i)){
                temp = run(s, i + 1, end, m);
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
        m[size] = -1;
        run(s, 0, size - 1, m);
        return m[0];
    }
};