/*
Search in Rotated Sorted Array Total Accepted: 7798 Total Submissions: 27848 My Submissions
Suppose a sorted array is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

You are given a target value to search. If found in the array return its index, otherwise return -1.

You may assume no duplicate exists in the array.
*/
/*
这题目的关键还是要找到已经sorted 的那一部分， 然后用那一部分来判定 d&c经典的题目， 和 find the kth in 2 sorted array 那一题目很像
*/
class Solution {
public:
    int search(int A[], int n, int target) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        int start = 0;
        int end = n - 1;
        int mid = 0;
        while(start <= end){
            mid = (start + end) / 2;
            if(A[mid] == target) return mid;
            if(A[mid] >= A[start]){
                if(A[mid] >= target && A[start] <= target){
                    end = mid - 1;
                }else{
                    start = mid + 1;
                }
            }
            else{
                if(A[mid] <= target && A[end] >= target){
                    start = mid + 1;
                }else{
                    end = mid - 1;
                }
            }
        }
        return -1;
    }
};

