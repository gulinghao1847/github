/*
Longest Common Prefix Total Accepted: 2372 Total Submissions: 8901 My Submissions
Write a function to find the longest common prefix string amongst an array of strings.
*/
class Solution {
public:
    string findPrefix(string a, string b){
        int min = a.size() < b.size() ? a.size() : b.size();
        string result;
        for(int idx = 0; idx < min; idx++){
            if(a[idx] == b[idx]) result.push_back(a[idx]);
            else break;
        }
        return result;
    }
    
    string run(vector<string> &strs, int start, int end){
        int size = end - start + 1;
        if(size == 1){
            return strs[start];
        }
        int mid = (start + end) / 2;
        string first = run(strs, start, mid);
        string second = run(strs, mid + 1, end);
        return findPrefix(first, second);
    }
	
    string longestCommonPrefix(vector<string> &strs) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        int s = strs.size();
        string res;
        if(s == 0) return res;
        return run(strs, 0, s - 1);
    }
};
