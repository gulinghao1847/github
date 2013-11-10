/**
Median of Two Sorted Arrays Total Accepted: 2286 Total Submissions: 14751 My Submissions
There are two sorted arrays A and B of size m and n respectively. Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).

Discuss

/*
A very hard problem.
I used divide and conquer to solve this problem.
Firstly, there is a problem called find the Kth element in two sorted array
So, we write a function called findKPosition first which is the hardedst part;
In this function:
Three boundry condition are listed below.
For the third boundry condition, if k == 1, then ka = (min(m, k/2) ) = 0 then ka - 1 < 0, which is illegal
As mentioned in the function, m < n.
Three condition:
(1) A[ka - 1] == B[kb - 1], then the kth number is A[ka - 1] = B[kb - 1];
(2) A[ka - 1] > B[kb - 1], then we delete the left part of B because the Kth element can't be in this part(all smaller than the Kth element)
(3) A[ka - 1] < B[kb - 1], then we delete the left part of A because the Kth element can't be in this part (all smaller than the Kth element)
After this, I wrote a function called: findMedianSortedArrays() to achieve the goal;
median = (m + n) % 2 == 1 ? ValueOf[(m+n) / 2]  :  ValueOf[((m + n)/2 + 1)] + ValueOf[((m + n)/2)] 
*/

class Solution {
public:
    double findKPosition(int A[],int m, int B[],int n, int k){
        if((m) > (n)){
            return findKPosition(B, n, A, m, k);
        }
        if(m <= 0){
            return B[k - 1];
        }
        if(k == 1){
            return min(A[0], B[0]);
        }
        int ka = min(m, k/2);
        int kb = k - ka;
        if(A[ka - 1] == B[kb - 1]) return A[ka - 1];
        else if(A[ka - 1] > B[kb - 1]){
            return findKPosition(A, m, B + kb, n - kb, k - kb);
        }
        else if(A[ka - 1] < B[kb - 1]){
            return findKPosition(A + ka, m - ka, B, n, k - ka);
        }
    }
    double findMedianSortedArrays(int A[], int m, int B[], int n) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        double ret = 0;
        if((m + n) %2 == 1){
            ret = findKPosition(A, m, B, n, (m + n) / 2 + 1);
        }else if((m + n) %2 == 0){
            ret = (findKPosition(A, m, B, n, (m + n) / 2) + findKPosition(A, m, B, n, (m + n)/2 + 1)) / 2.0;
        }
        return ret;
    }
};