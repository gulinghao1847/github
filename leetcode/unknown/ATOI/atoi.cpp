/**
String to Integer (atoi) Total Accepted: 1539 Total Submissions: 10618 My Submissions
Implement atoi to convert a string to an integer.

Hint: Carefully consider all possible input cases. If you want a challenge, please do not see below and ask yourself what are the possible input cases.

Notes: It is intended for this problem to be specified vaguely (ie, no given input specs). You are responsible to gather all the input requirements up front.

spoilers alert... click to show requirements for atoi.

Requirements for atoi:
The function first discards as many whitespace characters as necessary until the first non-whitespace character is found. Then, starting from this character, takes an optional initial plus or minus sign followed by as many numerical digits as possible, and interprets them as a numerical value.

The string can contain additional characters after those that form the integral number, which are ignored and have no effect on the behavior of this function.

If the first sequence of non-whitespace characters in str is not a valid integral number, or if no such sequence exists because either str is empty or it contains only whitespace characters, no conversion is performed.

If no valid conversion could be performed, a zero value is returned. If the correct value is out of the range of representable values, INT_MAX (2147483647) or INT_MIN (-2147483648) is returned.
 */
/*
本题目要注意的是 INT_MIN = -INT_MAX - 1;
*/
class Solution {
public:
    int atoi(const char *str) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        int result = 0;
        int pos = 0;
        while(*str == ' ') str++;  //white space
        if(*str == '+') 
        {
            pos = 1;
            str++;
        }
        else if(*str == '-') 
        {
            pos = 2;
            str++;
        }
        while(*str >= '0' && *str <='9'){
            if((result == 214748364 && *str > '7') || result > 214748364){
                return pos == 2 ? INT_MIN : INT_MAX;    /*IMPORTANT*/
            }
            result = result*10 + *str - '0';
            str++;
        }
        return pos == 2 ? -result : result;
    }
};