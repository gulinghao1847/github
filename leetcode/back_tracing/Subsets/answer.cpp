/*
Subsets Total Accepted: 5579 Total Submissions: 20743 My Submissions
Given a set of distinct integers, S, return all possible subsets.

Note:
Elements in a subset must be in non-descending order.
The solution set must not contain duplicate subsets.
For example,
If S = [1,2,3], a solution is:

[
  [3],
  [1],
  [2],
  [1,2,3],
  [1,3],
  [2,3],
  [1,2],
  []
]
*/
class Solution {
public:
    void run(vector<vector<int>>& result, vector<int>& now, vector<int>& S, int begin){
        result.push_back(now);
        
        int size = S.size();
        for(int i = begin; i < size; i++){
            now.push_back(S[i]);
            run(result, now, S, i + 1);
            now.pop_back();
        }
    }
    vector<vector<int> > subsets(vector<int> &S) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        vector<vector<int>> result;
        vector<int> now;
        sort(S.begin(), S.end());
        run(result, now, S, 0);
        return result;
    }
};