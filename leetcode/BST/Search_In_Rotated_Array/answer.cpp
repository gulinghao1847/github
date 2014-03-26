/*
Search in Rotated Sorted Array II Total Accepted: 6286 Total Submissions: 21216 My Submissions
Follow up for "Search in Rotated Sorted Array":
What if duplicates are allowed?

Would this affect the run-time complexity? How and why?

Write a function to determine if a given target is in the array.
*/
class Solution {
public:
    bool search(int A[], int n, int target) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        int start = 0;
        int end = n - 1;
        int mid = 0;
        while(start <= end){
            mid = (start + end) / 2;
            if(A[mid] == target) return true;
            if(A[mid] > A[start]){
                if(A[mid] >= target && A[start] <= target){
                    end = mid - 1;
                }else{
                    start = mid + 1;
                }
            }
            else if(A[mid] < A[start]){
                if(A[mid] <= target && A[end] >= target){
                    start = mid + 1;
                }else{
                    end = mid - 1;
                }
            }else{
                start++;
            }
        }
        return false;
    }
};

