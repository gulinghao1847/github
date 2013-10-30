/*
Subsets II Total Accepted: 1381 Total Submissions: 5191 My Submissions
Given a collection of integers that might contain duplicates, S, return all possible subsets.

Note:
Elements in a subset must be in non-descending order.
The solution set must not contain duplicate subsets.
For example,
If S = [1,2,2], a solution is:

[
  [2],
  [1],
  [1,2,2],
  [2,2],
  [1,2],
  []
]
*/
class Solution {
public:
    void run(vector<vector<int>>& result, vector<int>& S, int pos, vector<int> now){
        int end = S.size();
        result.push_back(now);
        if(pos == end){
            return;
        }
        for(int i = pos; i <end; i++){
            now.push_back(S[i]);
            run(result, S, i + 1, now);
            now.pop_back();
            while(i < end - 1 && S[i] == S[i + 1]) i++;
        }
    }
    vector<vector<int> > subsetsWithDup(vector<int> &S) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        sort(S.begin(), S.end());
        vector<vector<int>> result;
        vector<int> now;
        if(S.size() == 0){
            return result;
        }
        run(result, S, 0, now);
        return result;
    }
};