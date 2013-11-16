/*
Pascal's Triangle II Total Accepted: 2095 Total Submissions: 7064 My Submissions
Given an index k, return the kth row of the Pascal's triangle.

For example, given k = 3,
Return [1,3,3,1].

Note:
Could you optimize your algorithm to use only O(k) extra space?
*/
/*
	SIMPLE QUESTION
*/
class Solution {
public:
    vector<int> getRow(int rowIdx) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
                // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        vector<int> now;
        vector<int> last;
        last.push_back(1);
        int numRows = rowIdx + 1;
        if(numRows == 1) return last;
        for(int i = 2; i <= numRows; i++){
            now.push_back(1);
            for(int j = 2; j <= i - 1; j++){
                int num = last[j - 2] + last[j - 1];
                now.push_back(num);
            }
            now.push_back(1);
            last = now;
            now.clear();
        }
        return last;
    }
};

