/*
Remove Duplicates from Sorted Array Total Accepted: 8183 Total Submissions: 25190 My Submissions
Given a sorted array, remove the duplicates in place such that each element appear only once and return the new length.

Do not allocate extra space for another array, you must do this in place with constant memory.

For example,
Given input array A = [1,1,2],

Your function should return length = 2, and A is now [1,2].
*/
class Solution {
public:
    int removeDuplicates(int A[], int n) {
        int remove = 0;
        if(n == 0) return 0;
        int last = A[0];
        for(int i = 1; i < n; i++){
            if(A[i] == last){
                remove++;
                continue;
            }
            last = A[i];
            A[i - remove] = A[i];
            if(remove != 0) 
                A[i] = 0;
        }
        return n - remove;
    }
};

