class Solution {
public:
    int max(int a, int b){
        return a > b ? a : b;
    }
    bool canJump(int A[], int n) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        int reach = 0;
        for(int i = reach; i <= reach && reach < n; i++){
            reach = max(reach, A[i] + i);
        }
        return reach >= (n - 1);
    }
};