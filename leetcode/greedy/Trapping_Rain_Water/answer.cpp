/*
Trapping Rain Water Total Accepted: 5959 Total Submissions: 21325 My Submissions
Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it is able to trap after raining.

For example, 
Given [0,1,0,2,1,0,1,3,2,1,2,1], return 6.


The above elevation map is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being trapped. Thanks Marcos for contributing this image!
*/
class Solution {
public:
    int trap(int A[], int n) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        vector<int> front(n, 0);
        vector<int> end(n, 0);
        int maxHeight = 0;
        int res = 0;
        for(int i = 0; i < n; i++){
            front[i] = maxHeight;
            maxHeight = max(maxHeight, A[i]);
        }
        maxHeight = 0;
        for(int i = n - 1; i >= 0; i--){
            end[i] = maxHeight;
            maxHeight = max(maxHeight, A[i]);
        }
        for(int i = 0; i < n; i++){
            int height = max(min(front[i], end[i]) - A[i], 0);
            res += height;
        }
        return res;
    }
};

