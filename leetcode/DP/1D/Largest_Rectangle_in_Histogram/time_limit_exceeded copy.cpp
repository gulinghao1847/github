class Solution {
public:
    int largestRectangleArea(vector<int> &height) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        int size = height.size();
        vector<int> minHeight(size, -1);
        int max = INT_MIN;
        int cur = 0;
        for(int i = 0; i < size; i++){
            minHeight[i] = height[i];
            for(int j = 0; j <= i; j++){
                if(j != i){
                    minHeight[j] = min(minHeight[j], height[j]);
                }
                cur = minHeight[j] * (i - j + 1);
                if(cur > max) max = cur;
            }
        }
        return max;
    }
};