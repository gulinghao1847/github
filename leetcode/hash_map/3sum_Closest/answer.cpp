/*
3Sum Closest Total Accepted: 5563 Total Submissions: 20789 My Submissions
Given an array S of n integers, find three integers in S such that the sum is closest to a given number, target. Return the sum of the three integers. You may assume that each input would have exactly one solution.

    For example, given array S = {-1 2 1 -4}, and target = 1.

    The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
*/
class Solution {
public:
    int threeSumClosest(vector<int> &num, int target) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        int result = INT_MAX;
        sort(num.begin(), num.end());
        for(int i = 0; i < num.size() - 2; i++){
            int first = i;
            int second = i + 1;
            int third = num.size() - 1;
            int sum = 0;
            while(second < third){
                sum = num[first] + num[second] + num[third];
                if(sum > target){
                    third--;
                }else if(sum == target){
                    return sum;
                }else if(sum < target){
                    second++;
                }
                if(result == INT_MAX)
                    result = sum;
                else
                    result = abs(result - target) < abs(sum - target) ? result : sum;
            }
        }
        return result;
    }
};