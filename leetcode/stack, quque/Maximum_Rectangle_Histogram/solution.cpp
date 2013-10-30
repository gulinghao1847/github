/**
Largest Rectangle in Histogram Total Accepted: 1410 Total Submissions: 7165 My Submissions
Given n non-negative integers representing the histogram's bar height where the width of each bar is 1, find the area of largest rectangle in the histogram.


Above is a histogram where width of each bar is 1, given height = [2,1,5,6,2,3].


The largest rectangle is shown in the shaded area, which has area = 10 unit.

For example,
Given height = [2,1,5,6,2,3],
return 10.
*/
class Solution {
public:
    int largestRectangleArea(vector<int> &height) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        /*
        int size = height.size();
        vector<int> minHeight(size, -1);
        int max = INT_MIN;
        int cur = 0;
        for(int i = 0; i < size; i++){
            minHeight[i] = height[i];
            for(int j = 0; j <= i; j++){
                if(j != i){
                    minHeight[j] = min(minHeight[j], height[i]);
                }
                cur = minHeight[j] * (i - j + 1);
                if(cur > max) max = cur;
            }
        }
        return max;
        */
        stack<int> idx;
        int maxArea = 0;
        int i = 0;
        vector<int> h(height);
        h.push_back(0);
        while(i < h.size()){
            if(idx.empty() || h[i] >= h[idx.top()]){
                idx.push(i++);
            }else{
                int single = idx.top();
                idx.pop();
                maxArea = max(maxArea, h[single]*(idx.empty() ?  i : (i - idx.top() - 1)));
            }
        }
        return maxArea;
    }
};