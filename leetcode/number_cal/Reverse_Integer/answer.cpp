/*
Reverse Integer Total Accepted: 11498 Total Submissions: 28796 My Submissions
Reverse digits of an integer.

Example1: x = 123, return 321
Example2: x = -123, return -321

click to show spoilers.

Have you thought about this?
Here are some good questions to ask before coding. Bonus points for you if you have already thought through this!

If the integer's last digit is 0, what should the output be? ie, cases such as 10, 100.

Did you notice that the reversed integer might overflow? Assume the input is a 32-bit integer, then the reverse of 1000000003 overflows. How should you handle such cases?

Throw an exception? Good, but what if throwing an exception is not an option? You would then have to re-design the function (ie, add an extra parameter).
*/
class Solution {
public:
    int reverse(int x) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        long long num = x;
        num = num < 0 ? -num : num;
        long long result = 0;
        while(num > 0){
            result = result * 10 + num%10;
            num = num/10;
        }
        if(x < 0){
            if(result <= INT_MIN){
                return INT_MIN;
            }else{
                return (int)(-result);
            }
        }else{
            if(result > INT_MAX){
                return INT_MAX;
            }else{
                return (int)result;
            }
        }
    }
};
/*
凡是涉及到基础变量的时候， 千万要小心， 注意， 如果要把负数转化成正数的， 要记得INT_MIN 无法转化成正的（在int范围内） 要转化成long long 才可以。
*/

