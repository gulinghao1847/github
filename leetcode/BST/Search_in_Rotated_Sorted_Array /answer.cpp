/*
Search in Rotated Sorted Array Total Accepted: 2879 Total Submissions: 10400 My Submissions
Suppose a sorted array is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

You are given a target value to search. If found in the array return its index, otherwise return -1.

You may assume no duplicate exists in the array.
*/
/*
V(index) means the value of index
----------------------------------------
|                  |                   |
|                  |                   |
----------------------------------------
start             mid                  end

condition 1 : V(mid) > target
    (1) V(start) > V(mid)     the value should be between start and mid
	(2) V(start) < V(mid):
		V(start) > target:     the value should be between mid and end
		V(start) < target:    the value should be between start and mid

condition 2: V(mid) < target:
	(1) V(end) < target: the value should be between start and mid
	else : the value should be between mid and end

condition 3: V(mid) ==  target: return mid
*/
class Solution {
public:
    int search(int A[], int n, int target) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        int mid = 0;
        int start = 0;
        int end = n - 1;
        while(start <= end){
            mid = (start + end) / 2;
            if(A[mid] == target) return mid;
            if(A[mid] > target){
                if(A[start] > target){
                    if(A[start] > A[mid]){
                        end = mid - 1;
                    }else{
                        start = mid + 1;
                    }
                }else{
                    end = mid - 1;
                }
            }else{
                if(A[end] >= target){
                    start = mid + 1;
                }else{
                    if(A[end] < A[mid]){
                        start = mid + 1;
                    }else{
                        end = mid - 1;
                    }
                }
            }
        }
        return -1;
    }
};

