/**
4Sum Total Accepted: 1158 Total Submissions: 5217 My Submissions
Given an array S of n integers, are there elements a, b, c, and d in S such that a + b + c + d = target? Find all unique quadruplets in the array which gives the sum of target.

Note:
Elements in a quadruplet (a,b,c,d) must be in non-descending order. (ie, a ≤ b ≤ c ≤ d)
The solution set must not contain duplicate quadruplets.
    For example, given array S = {1 0 -1 0 -2 2}, and target = 0.

    A solution set is:
    (-1,  0, 0, 1)
    (-2, -1, 1, 2)
    (-2,  0, 0, 2)
 */
/*
这里要注意的就是26, 27, 28, 29行排除duplicate的条件的判断， 其他没有问题
*/
class Solution {
public:
    vector<vector<int> > fourSum(vector<int> &num, int target) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        sort(num.begin(), num.end());
        int size = num.size();
        vector<int> input(4);
        vector<vector<int>> result;
        for(int i = 0; i < size - 3; i++){
            while(i > 0 && num[i] == num[i - 1]) i++;
            for(int j = i + 1; j < size - 2; j++){
                while(j > i + 1 && num[j] == num[j - 1]) j++;
                int third = j + 1;
                int forth = size - 1;
                int sig = 0;
                int mem = 0;
                while(third < forth){
                    int sum = num[i] + num[j] + num[third] + num[forth];
                    if(sum < target){
                        third++;
                    }else if(sum > target){
                        forth--;
                    }else if(sum == target && ((sig == 1 && num[third] != mem) || sig == 0)){
                        input[0] = num[i];
                        input[1] = num[j];
                        input[2] = num[third];
                        input[3] = num[forth];
                        result.push_back(input);
                        sig = 1;
                        mem = num[third];
                        third++;
                        forth--;
                    }else{
                        third++;
                        forth--;
                    }
                }
            }
        }
        return result;
    }
};