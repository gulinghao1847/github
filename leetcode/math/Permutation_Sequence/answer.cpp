/*
Permutation Sequence Total Accepted: 4880 Total Submissions: 23056 My Submissions
The set [1,2,3,…,n] contains a total of n! unique permutations.

By listing and labeling all of the permutations in order,
We get the following sequence (ie, for n = 3):

"123"
"132"
"213"
"231"
"312"
"321"
Given n and k, return the kth permutation sequence.

Note: Given n will be between 1 and 9 inclusive.
*/
class Solution {
public:
    string getPermutation(int n, int k) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        vector<int> n1(n + 1, 0);
        vector<int> num(n, 0);
        string result;
        n1[0] = 1;
        for(int i = 1; i <= n; i++){
            n1[i] = n1[i - 1] * i;
            num[i - 1] = i;
        }
        int value = k - 1;
        int now = 0;
        for(int i = n - 1 ; i >= 0; i--){
            now = value/n1[i];
            value = value%n1[i];
            result = result + (char)(num[now] + '0');
            num.erase(num.begin() + now);
        }
        return result;
    }
};

