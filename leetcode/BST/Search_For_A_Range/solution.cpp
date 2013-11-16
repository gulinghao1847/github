/*
Search for a Range Total Accepted: 2136 Total Submissions: 8022 My Submissions
Given a sorted array of integers, find the starting and ending position of a given target value.

Your algorithm's runtime complexity must be in the order of O(log n).

If the target is not found in the array, return [-1, -1].

For example,
Given [5, 7, 7, 8, 8, 10] and target value 8,
return [3, 4].
*/
/*
a derivation of BST,  the runtime complexity must be in the order of O(log n).
So, we need to have a algorithm to find the starting and ending position seperately using O(log n), thats the start point of the following algorithm
But I think this algorithm is 2 complex, maybe I can find a easier way to solve this problem.(We can combine these two functions as only 2 lines of the code are different)
*/
class Solution {
public:
    int findFirst(int A[], int begin, int size, int target){
        if(size <= 0) return -1;
        int mid = (begin + (begin + size - 1)) / 2;
        if(A[mid] == target){
            if(mid != begin && A[mid] == A[mid - 1]){
                return findFirst(A, begin, mid - begin, target);
            }else
            return mid;
        }else if(A[mid] > target){
            return findFirst(A, begin, mid - begin, target);
        }else if(A[mid] < target){
            return findFirst(A, mid + 1, begin + size - mid - 1, target);
        }
    }
	
    int findLast(int A[], int begin, int size, int target){
        if(size <= 0) return -1;
        int end = begin + size - 1;
        int mid = (begin + end) / 2;
        if(A[mid] == target){
            if(mid != end && A[mid] == A[mid + 1]){
                return findLast(A, mid + 1, end - mid, target);
            }else
            return mid;
        }else if(A[mid] > target){
            return findLast(A, begin, mid - begin, target);
        }else if(A[mid] < target){
            return findLast(A, mid + 1, begin + size - mid - 1, target);
        }
    }
	
    vector<int> searchRange(int A[], int n, int target) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        vector<int> result;
        //find the first and the last seperately each is O(logN)
        result.push_back(findFirst(A, 0, n, target));
        result.push_back(findLast(A, 0, n, target));
        return result;
    }
};