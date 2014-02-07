/*
Letter Combinations of a Phone Number Total Accepted: 4734 Total Submissions: 18795 My Submissions
Given a digit string, return all possible letter combinations that the number could represent.

A mapping of digit to letters (just like on the telephone buttons) is given below.



Input:Digit string "23"
Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
Note:
Although the above answer is in lexicographical order, your answer could be in any order you want.
*/
class Solution {
public:
    string getValue(char num){
        switch(num){
            case '1':return "";
            case '2':return "abc";
            case '3':return "def";
            case '4':return "ghi";
            case '5':return "jkl";
            case '6':return "mno";
            case '7':return "pqrs";
            case '8':return "tuv";
            case '9':return "wxyz";
            default:return "";
        }
    }
    
    void run(vector<string>& res, string& now, string& digits, int start){
        int size = digits.size();
        if(start == size){
            res.push_back(now);
            return;
        }
        string value = getValue(digits[start]);
        int s1 = value.size();
        for(int i = 0; i < s1; i++){
            now.push_back(value[i]);
            run(res, now, digits, start + 1);
            now.pop_back();
        }
    }
    
    vector<string> letterCombinations(string digits) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        vector<string> res;
        string now;
        if(digits.size() == 0){ res.push_back(now);return res;}
        run(res, now, digits, 0);
        return res;
    }
};

