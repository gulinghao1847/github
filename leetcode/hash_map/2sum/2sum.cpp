/**
Two Sum
Given an array of integers, find two numbers such that they add up to a specific target number.

The function twoSum should return indices of the two numbers such that they add up to the target, where index1 must be less than index2. Please note that your returned answers (both index1 and index2) are not zero-based.

You may assume that each input would have exactly one solution.

Input: numbers={2, 7, 11, 15}, target=9
Output: index1=1, index2=2
 */
/*
凡是考虑到快速查找某一个数或者一个string等等， 只要是数据， 就要用hash_map
*/
class Solution {
public:
    vector<int> twoSum(vector<int> &numbers, int target) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        map<int,int> mp;
        int size = numbers.size();
        vector<int> result;
        for(int i = 0; i < size; i++){
            mp[numbers[i]] = i;
        }
        for(int i = 0; i < size; i++){
            int ano = target - numbers[i];
            if(mp.find(ano) != mp.end()){
                result.push_back(i + 1);
                result.push_back(mp[ano] + 1);
                break;
            }
        }
        return result;
    }
};