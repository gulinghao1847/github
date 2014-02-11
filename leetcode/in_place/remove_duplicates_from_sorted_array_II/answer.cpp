/*
Remove Duplicates from Sorted Array II Total Accepted: 5597 Total Submissions: 18842 My Submissions
Follow up for "Remove Duplicates":
What if duplicates are allowed at most twice?

For example,
Given sorted array A = [1,1,1,2,2,3],

Your function should return length = 5, and A is now [1,1,2,2,3].
*/
class Solution {
public:
    int removeDuplicates(int A[], int n) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        int remove = 0;
        if(n == 0) return 0;
        int last = A[0];
        int app = 1;
        for(int i = 1; i < n; i++){
            //first
            if(A[i] != last){
                app = 1;
            }
            if(A[i] == last){
                //second
                if(app == 1){
                    app++;
                }
                else if(app == 2){
                    remove++;
                    continue;
                }
            }
            A[i - remove] = A[i];
            last = A[i];
        }
        return n - remove;
    }
};

