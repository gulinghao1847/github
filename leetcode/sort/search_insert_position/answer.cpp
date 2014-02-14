/*
Search Insert Position Total Accepted: 8136 Total Submissions: 23863 My Submissions
Given a sorted array and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.

You may assume no duplicates in the array.

Here are few examples.
[1,3,5,6], 5 → 2
[1,3,5,6], 2 → 1
[1,3,5,6], 7 → 4
[1,3,5,6], 0 → 0
*/
class Solution {
public:
    int searchInsert(int A[], int n, int target) {
        int start = 0;
        int end = n - 1;
        int mid = (start + end) / 2;
        while(start <= end){
            mid = (start + end) / 2;
            if(A[mid] == target){
                return mid;
            }else if(A[mid] > target){
                end = mid - 1;
            }else if(A[mid] < target){
                start = mid + 1;
            }
        }
        if(A[mid] > target){
            return mid;
        }else{
            return mid + 1;
        }
    }
};