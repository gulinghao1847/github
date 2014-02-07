/*
First Missing Positive Total Accepted: 4907 Total Submissions: 22588 My Submissions
Given an unsorted integer array, find the first missing positive integer.

For example,
Given [1,2,0] return 3,
and [3,4,-1,1] return 2.

Your algorithm should run in O(n) time and uses constant space.
*/
class Solution {
public:
    int firstMissingPositive(int A[], int n) {
        vector<int> B(n, 0);
        int ret = 0;
        for(int i = 0; i < n; i++){
            if(A[i] > 0 && A[i] <= n){
                B[A[i] - 1] = 1;
            }
        }
        for(int i = 0; i < n; i++){
            if(B[i] == 0){
                ret = i + 1;
                break;
            }
        }
        if(ret == 0){
            ret = n + 1;
        }
        return ret;
    }
};

