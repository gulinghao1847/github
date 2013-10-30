/**
Permutations Total Accepted: 2060 Total Submissions: 6845 My Submissions
Given a collection of numbers, return all possible permutations.

For example,
[1,2,3] have the following permutations:
[1,2,3], [1,3,2], [2,1,3], [2,3,1], [3,1,2], and [3,2,1].
 */
class Solution {
public:
    void run(vector<vector<int>>& result, vector<int>& now, vector<int>& used, int number, vector<int> &num){
        int size = num.size();
        if(number == size){
            result.push_back(now);
            return;
        }
        for(int i = 0; i < size; i++){
            if(used[i] == 1) continue;
            used[i] = 1;
            now.push_back(num[i]);
            run(result, now, used, number + 1, num);
            now.pop_back();
            used[i] = 0;
        }
    }
    vector<vector<int> > permute(vector<int> &num) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        int size = num.size();
        vector<int> used(size, 0);
        vector<vector<int>> result;
        vector<int> now;
        run(result, now, used, 0, num);
        return result;
    }
};