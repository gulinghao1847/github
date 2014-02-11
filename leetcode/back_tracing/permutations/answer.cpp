/*T
Permutations Total Accepted: 7286 Total Submissions: 23649 My Submissions
Given a collection of numbers, return all possible permutations.

For example,
[1,2,3] have the following permutations:
[1,2,3], [1,3,2], [2,1,3], [2,3,1], [3,1,2], and [3,2,1].
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
        }
    }
    vector<vector<int> > permute(vector<int> &num) {
        vector<vector<int>> result;
        vector<int> now;
        run(num, result, now);
        return result;
    }
};

