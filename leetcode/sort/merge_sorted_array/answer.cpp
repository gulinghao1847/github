/*
Merge Sorted Array Total Accepted: 6948 Total Submissions: 21627 My Submissions
Given two sorted integer arrays A and B, merge B into A as one sorted array.

Note:
You may assume that A has enough space to hold additional elements from B. The number of elements initialized in A and B are m and n respectively.

Discuss


*/
//from tail to head
class Solution {
public:
    void merge(int A[], int m, int B[], int n) {
        int count1 = m - 1;
        int count2 = n - 1;
        //
        int k = m + n - 1;
        for(; count1 >= 0 && count2 >= 0;k--){
            if(A[count1] > B[count2]){
                A[k] = A[count1];
                count1--;
            }else{
                A[k] = B[count2];
                count2--;
            }
        }
		//we only need to consider when A is empty because if array B is empty, then A has been sorted.
        while(count2 >= 0){
            A[k--] = B[count2--];
        }
    }
};
