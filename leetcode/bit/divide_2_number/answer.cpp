/*
Divide Two Integers Total Accepted: 1776 Total Submissions: 11884 My Submissions
Divide two integers without using multiplication, division and mod operator.
*/
class Solution {
public:
    int divide(int dividend, int divisor) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        long long a = abs((double)dividend);   /*abs(INT_MIN) cant be represented by positive int value, so cast it to double, and then stored as long long */
        long long b = abs((double)divisor);
        int res = 0;
        while(a >= b){
            long long c = b;
            int i = 0;
            while(a >= c){
                a -=c;
                res += 1 << i;
                i++;
                c <<= 1;
            }
        }
        return (dividend^divisor)  >> 31 ? (-res) : res;
    }
};