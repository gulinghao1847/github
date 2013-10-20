class Solution {
public:
    string getPermutation(int n, int k) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        vector<int> n1(n + 1, 0);
        vector<int> num(n, 0);
        string result;
        n1[0] = 1;
        for(int i = 1; i <= n; i++){
            n1[i] = n1[i - 1] * i;
            num[i - 1] = i;
        }
        int value = k - 1;
        int now = 0;
        for(int i = n - 1 ; i >= 0; i--){
            now = value/n1[i];
            value = value%n1[i];
            result = result + (char)(num[now] + '0');
            num.erase(num.begin() + now);
        }
        return result;
    }
};