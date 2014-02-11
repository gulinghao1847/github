/*
Permutations II Total Accepted: 4986 Total Submissions: 20145 My Submissions
Given a collection of numbers that might contain duplicates, return all possible unique permutations.

For example,
[1,1,2] have the following unique permutations:
[1,1,2], [1,2,1], and [2,1,1].
*/
class Solution {
public:
    void run(vector<int>& num, vector<vector<int>>& result, vector<int>& now){
        if(num.size() == 0){
            result.push_back(now);
            return;
        }
        for(int i = 0; i < num.size(); i++){
            int val = num[i];
            now.push_back(val);
            num.erase(num.begin() + i);
            run(num, result, now);
            num.insert(num.begin() + i, val);
            now.pop_back();
            while(i < num.size() - 1 && num[i + 1] == num[i])i++;
        }
    }
    vector<vector<int> > permuteUnique(vector<int> &num) {
        vector<vector<int>> result;
        vector<int> now;
        sort(num.begin(), num.end());
        run(num, result, now);
        return result;
    }
};

