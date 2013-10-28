class Solution {
public:
    void run(int& count, int l, int r){
        if(l > r) return;
        if(l == r){
            count++;
            return;
        }
        for(int i = l; i <= r; i++){
            run(count, l, i - 1);
            run(count, i + 1, r);
        }
    }
    int numTrees(int n) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        int count = 0;
        run(count, 1, n);
        return count;
    }
};