class Solution {
public:
    bool canJump(int A[], int n) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        vector<bool> m(n, false);
        m[n - 1] = true;
        for(int i = n - 2; i >= 0; i--){
            for(int j = i + 1; j < n ; j++){
                if(m[j] == true && A[i] >= (j - i)){
                    m[i] = true;
                    break;
                }
            }
        }
        return m[0];
    }
};