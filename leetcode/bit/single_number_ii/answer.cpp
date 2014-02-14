/*
Single Number II Total Accepted: 8118 Total Submissions: 25736 My Submissions
Given an array of integers, every element appears three times except for one. Find that single one.

Note:
Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?
*/
class Solution {
public:
    int singleNumber(int A[], int n) {
        int result = 0;
        for(int i = 0; i < 32; i++){
            int bit = 0;
            for(int j = 0; j < n; j++){
                if((A[j] & (1 << i)) != 0)bit++;
            }
            bit = bit%3;
            result = result | (bit << i);
        }
        return result;
    }
};
