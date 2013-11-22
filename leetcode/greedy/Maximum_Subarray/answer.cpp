/*
Maximum Subarray Total Accepted: 3567 Total Submissions: 10979 My Submissions
Find the contiguous subarray within an array (containing at least one number) which has the largest sum.

For example, given the array [−2,1,−3,4,−1,2,1,−5,4],
the contiguous subarray [4,−1,2,1] has the largest sum = 6.

click to show more practice.

More practice:
If you have figured out the O(n) solution, try coding another solution using the divide and conquer approach, which is more subtle.
*/
/*
GREEDY ALGORITHM, HARD PROBLEM
*/
class Solution {
public:
    int maxSubArray(int A[], int n) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        int res = INT_MIN;
        int sum = 0;
        for(int i = 0; i < n; i++){
            if(A[i] < 0) {
                sum = sum + A[i];
                res = res < sum ? sum : res;
                if(sum < 0) sum = 0;
            }else{
                sum = sum + A[i];
                res = res < sum ? sum : res;
            }
        }
        return res;
    }
};

