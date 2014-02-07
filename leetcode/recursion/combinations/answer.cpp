/*

Combinations Total Accepted: 5769 Total Submissions: 19562 My Submissions
Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.

For example,
If n = 4 and k = 2, a solution is:

[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]
*/
class Solution {
public:
    void run(vector<vector<int>>& result, vector<int>& now, int n, int k, int begin, int num){
        if(num == k){
            result.push_back(now);
            return;
        }
        if(n < k - num + begin - 1) 
            return;
        for(int i = begin; i <= n; i++){
            now.push_back(i);
            run(result, now, n, k, i + 1, num + 1);
            now.pop_back();
        }
    }
    vector<vector<int> > combine(int n, int k) {
        vector<vector<int>> result;
        vector<int> now;
        run(result, now, n, k, 1, 0);
        return result;
    }
};

