/*
Plus One Total Accepted: 2565 Total Submissions: 8670 My Submissions
Given a number represented as an array of digits, plus one to the number.
*/
class Solution {
public:
    vector<int> plusOne(vector<int> &digits) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        int size = digits.size();
        digits[size - 1] += 1;
        int inc = 0;
        for(int i = size - 1; i >= 0; i--){
            int num = digits[i] + inc;
            digits[i] = num % 10;
            inc = num / 10;
            if(inc == 0){
                break;
            }
        }
        if(inc != 0){
            digits.insert(digits.begin(), inc);
        }
        return digits;
    }
};

