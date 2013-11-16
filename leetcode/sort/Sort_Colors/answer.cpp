/*
Sort Colors Total Accepted: 2393 Total Submissions: 8175 My Submissions
Given an array with n objects colored red, white or blue, sort them so that objects of the same color are adjacent, with the colors in the order red, white and blue.

Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.

Note:
You are not suppose to use the library's sort function for this problem.

click to show follow up.

Follow up:
A rather straight forward solution is a two-pass algorithm using counting sort.
First, iterate the array counting number of 0's, 1's, and 2's, then overwrite array with total number of 0's, then 1's and followed by 2's.

Could you come up with an one-pass algorithm using only constant space?
*/
class Solution {
public:
    void sortColors(int A[], int n) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        int r = 0;
        int w = 0;
        int b = 0;
        for(int i = 0; i < n; i++){
            if(A[i] == 0) r++;
            else if(A[i] == 1) w++;
            else if(A[i] == 2) b++;
        }
        for(int i = 0; i < n; i++){
            if(i < r) A[i] = 0;
            else if(i >= r && i < r + w) A[i] = 1;
            else if(i >= r + w) A[i] = 2;
        }
    }
};

