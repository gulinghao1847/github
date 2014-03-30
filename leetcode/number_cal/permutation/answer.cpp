/*
Permutation Sequence Total Accepted: 5592 Total Submissions: 26387 My Submissions
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
        vector<int> permutation(n + 1, 0);
        permutation[0] = 1;
        string result;
        vector<int> num(n, 1);
        for(int i = 1; i <= n; i++){
            num[i - 1] = i;
            permutation[i] = permutation[i - 1] * num[i - 1]; 
        }
		//from zero, minus 1
        k = k - 1;
        for(int count = n - 1; count >= 0; count--){
            int seq = k/permutation[count];
            k = k%permutation[count];
            result.push_back('0' + num[seq]);
            num.erase(num.begin() + seq);
        }
        return result;
    }
};

