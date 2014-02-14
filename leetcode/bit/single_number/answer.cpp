/*
Single Number Total Accepted: 11663 Total Submissions: 25815 My Submissions
Given an array of integers, every element appears twice except for one. Find that single one.

Note:
Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?
*/
/*
if we want to find this single number, using hash_map is a simple way and it is trival. Another way to solve this problem is using bit manipulation.
Using XOR. Using a loop to find it
if we have 5, 5, 6
we do
101^101^110, since x^x = 0 x^0=x, then we can find the single one
*/

class Solution {
public:
    int hashmapFunction(int A[], int n){
        map<int, int> mp;
        for(int i = 0; i < n; i++) mp[A[i]]++;
        map<int, int>::iterator it;
        for(it = mp.begin(); it != mp.end(); it++){
            if(it -> second == 1){
                return it -> first;
            }
        }
    }
    int bitManipulation(int A[], int n){
        int res = 0;
        for(int i = 0; i < n; i++){
            res = res ^ A[i];
        }
        return res;
    }
    int singleNumber(int A[], int n) {
        int result = hashmapFunction(A, n);
        result = bitManipulation(A, n);
        return result;
    }
};

