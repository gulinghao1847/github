/*
Multiply Strings Total Accepted: 5589 Total Submissions: 28233 My Submissions
Given two numbers represented as strings, return multiplication of the numbers as a string.

Note: The numbers can be arbitrarily large and are non-negative.
*/
class Solution {
public:
    int getInt(char a){
        return a - '0';
    }
    string multiply(string num1, string num2) {
        //no space and non-negative
        string result(num1.size() + num2.size() + 1, '0');
        std::reverse(num1.begin(), num1.end());
        std::reverse(num2.begin(), num2.end());
        int carry = 0;
        for(int i = 0; i < num2.size(); i++){
            //string singleResult;
            int re = 0;
            for(int j = 0; j < num1.size(); j++){
                re = carry + getInt(num1[j]) * getInt(num2[i]) + getInt(result[i + j]);
                carry = re/10;
                re = re%10;
                result[i + j] = re + '0';
            }
            if(carry > 0)
            {
                result[i+num1.size()] += carry;
                carry = 0;
            }
        }
        reverse(result.begin(), result.end());
        int start =0;
        while(result[start] =='0' && start < result.size())
        {
            start++;
        }
        if(start == result.size()) return "0";
        return result.substr(start, result.size()-start);
    }
};

