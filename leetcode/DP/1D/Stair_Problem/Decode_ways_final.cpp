class Solution {
public:
    int numDecodings(string s) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        int size = s.size();
        if(size == 0) return 0;
        vector<int> num(size + 1, 0);
        num[0] = 1;
        for(int i = 1; i <= size; i++){
            int n1 = 0;
            int n2 = 0;
            if(s[i - 1] != '0'){
                num[i] = num[i - 1];
            }
            if(i >= 2 &&(s[i - 2] == '1' || ((s[i - 2] == '2') && (s[i - 1] <= '6')))){
                num[i] += num[i - 2];
            }
        }
        return num[size];
    }
};