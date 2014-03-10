/*
Pow(x, n) Total Accepted: 8493 Total Submissions: 33017 My Submissions
Implement pow(x, n).
*/
/*
	这道题目在22行的时候出现了问题， 原来直接一个function可以搞定， 可是如果出现了n = INT_MIN 的时候， 就无法转成int 了， 必须专门写一个函数， 让他变成正数
*/
class Solution{
public:
    double power(double x, long long num){
        if(num == 1) return x;
        if(num == 0) return 1;
        double val = pow(x, num/2);
        if(num%2 == 0){
            return val*val;
        }
        return val*val*x;
    }
    double pow(double x, int n){
        long long num = n;
        if(num < 0){
            return (double)1/power(x, -num);
        }
        return power(x, num);
    }
};

