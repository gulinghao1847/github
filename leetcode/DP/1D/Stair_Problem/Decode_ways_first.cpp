class Solution {
public:
    int run(string& s, vector<int>& num, int begin){
        if(num[begin] != 0){
            return num[begin];
        }
        if(s[begin] == '0'){
            num[begin] = num[begin - 1];
        }
        
        int n1 = s[begin] - '0';
        int n2 = s[begin + 1] - '0';
        int ret = 0;
        if(n1*10 + n2 > 26){
            ret = run(s,num,begin + 2);
        }
        if(n1*10 + n2 <= 26){
            if(n2 == 0){
                ret = run(s,num,begin + 2);
            }else{
                ret = run(s,num,begin + 1) + run(s, num, begin + 2);
            }
        }
        num[begin] = ret;
        return ret;
    }
    int numDecodings(string s) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        int size = s.size();
        if(size == 0) return 0;
        if(size == 1 && s[0] == '0') return 0;
        
        vector<int> num(size + 1, 0);
        num[size] = 1;
        num[size - 1] = 1;
        int result = run(s, num, 0);
        return result;
    }
};