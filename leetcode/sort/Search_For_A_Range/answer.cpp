/*
Search for a Range Total Accepted: 6173 Total Submissions: 23273 My Submissions
Given a sorted array of integers, find the starting and ending position of a given target value.

Your algorithm's runtime complexity must be in the order of O(log n).

If the target is not found in the array, return [-1, -1].

For example,
Given [5, 7, 7, 8, 8, 10] and target value 8,
return [3, 4].

*/
/*
solution 1:
*/
class Solution {
public:
    int findFirst(int A[], int n, int target){
        int mid = n/2;
        int start = 0;
        int end = n - 1;
        while(start <= end){
            mid = (start + end) / 2;
            if(A[mid] == target){
                if(mid != 0){
                    if(A[mid] != A[mid - 1]){
                        return mid;
                    }else{
                        end = mid - 1;
                    }
                }else{
                    return mid;
                }
            }
            else if(A[mid] > target){
                end = mid - 1;
            }
            else if(A[mid] < target){
                start = mid + 1;
            }
        }
        return -1;
    }
    int findLast(int A[], int n, int target){
        int mid = n / 2;
        int start = 0;
        int end = n - 1;
        while(start <= end){
            mid = (start + end) / 2;
            if(A[mid] == target){
                if(mid == n - 1){
                    return mid;
                }else{
                    if(A[mid] == A[mid + 1]){
                        start = mid + 1;
                    }else{
                        return mid;
                    }
                }
            }
            else if(A[mid] > target){
                end = mid - 1;
            }
            else if(A[mid] < target){
                start = mid + 1;
            }
        }
        return -1;
    }
    vector<int> searchRange(int A[], int n, int target) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        vector<int> result;
        //find first
        int first = findFirst(A, n, target);
        int last = findLast(A, n, target);
        result.push_back(first);
        result.push_back(last);
        return result;
    }
};

/*
Solution 2:
*/
class Solution {
public:

    int findFirst(int A[], int a, int b, int target){
        if(a > b) return -1;
        int mid = (a + b)/2;
        if(A[mid] < target){
            return findFirst(A, mid + 1, b, target);
        }else if(A[mid] == target){
            if(mid != a &&A[mid] == A[mid - 1]){
                return findFirst(A, a, mid - 1, target);
            }else 
                return mid;
        }else{
            return findFirst(A, a, mid - 1, target);
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
        result.push_back(findFirst(A, 0, n, target));
        result.push_back(findLast(A, 0, n, target));
        return result;
    }
};
