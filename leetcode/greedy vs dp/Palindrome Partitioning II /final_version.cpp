class Solution {
public:
    int minCut(string s) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        int size = s.size();
        if(!size) return 0;
        vector<int> m(size + 1, INT_MAX);
        vector<vector<bool>> palin(size, vector<bool>(size, false));

        for(int i = 0; i < size; i++) palin[i][i] = true;
        
        m[size] = -1;
        for(int i = size - 1; i>=0; i--){
            int min = INT_MAX;
            for(int j = i; j <= size - 1; j++){
                if(s[i] == s[j] && (j - i < 2 || palin[i + 1][j - 1])){
                    palin[i][j] = true;
                    min = (min > (m[j + 1] + 1))?(m[j + 1] + 1):min;
                }
            }
            m[i] = min;
        }
        return m[0];
    }
};