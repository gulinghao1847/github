/*
Pascal's Triangle Total Accepted: 2412 Total Submissions: 7646 My Submissions
Given numRows, generate the first numRows of Pascal's triangle.

For example, given numRows = 5,
Return

[
     [1],
    [1,1],
   [1,2,1],
  [1,3,3,1],
 [1,4,6,4,1]
]
*/
/*
Simple Question, just remember: except corner cases: for every level: value[i] = value[i - 1] + value[i](in the previous level);
*/
class Solution {
public:
    vector<vector<int> > generate(int numRows) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        vector<vector<int>> result;
        if(numRows == 0) return result;
        vector<int> now;
        vector<int> last;
        last.push_back(1);
        result.push_back(last);
        for(int i = 2; i <= numRows; i++){
            now.push_back(1);
            for(int j = 2; j <= i - 1; j++){
                int num = last[j - 2] + last[j - 1];
                now.push_back(num);
            }
            now.push_back(1);
            result.push_back(now);
            last = now;
            now.clear();
        }
        return result;
    }
};

