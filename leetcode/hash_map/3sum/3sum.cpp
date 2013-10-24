/**
3Sum
Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

Note:
Elements in a triplet (a,b,c) must be in non-descending order. (ie, a ≤ b ≤ c)
The solution set must not contain duplicate triplets.
    For example, given array S = {-1 0 1 2 -1 -4},

    A solution set is:
    (-1, 0, 1)
    (-1, -1, 2)
 
 */
/*
这里的解法是， 依次对每个i 进行找其相应的j 和 k， 如果能找到， 就push 这里还要注意对于duplicate的查找的问题， 分为两个部分。 第一个是i， 不能重复， 第二步是在同一个i的情况下， j ， k 不能重复。
之前要sort， 解完
*/
class Solution {
public:
    vector<vector<int> > threeSum(vector<int> &num) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        sort(num.begin(), num.end());
        vector<vector<int>> result;
        vector<int> now(3,0);
        int size = num.size();
        for(int i = 0; i < size; i++){
            if(i != 0 && num[i] == num[i - 1]) continue;
            int j = i + 1;
            int k = size - 1;
            int preJ = 0;
            int preK = 0;
            int set = 0;
            while(j < k){
                int sum3 = num[i] + num[j] + num[k];
                if(sum3 > 0){
                    k--;
                }else if(sum3 < 0){
                    j++;
                }else if(set == 0 || (preJ != num[j] || preK != num[k])){
                    now[0] = num[i];
                    now[1] = num[j];
                    now[2] = num[k];
                    preK = num[k];
                    preJ = num[j];
                    set = 1;
                    j++;
                    k--;
                    result.push_back(now);
                }else{
                    j++;
                    k--;
                }
            }
        }
        return result;
    }
};