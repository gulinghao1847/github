/*
Sqrt(x) Total Accepted: 2994 Total Submissions: 14302 My Submissions
Implement int sqrt(int x).

Compute and return the square root of x.
*/
/*
The idea of this problem is trivial, but we need to pay attentaion to some details.
*/
class Solution {
public:
    int sqrt(int x) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
		/*
		firstly, we need to transform all the numbers to long long
		*/
        long long mid = 0;
        long long begin = 1;
        long long end = (long long)x;
        while(begin <= end){
            mid = (begin + end) / 2;
            long long num = mid * mid;
            if(num == x){
                return mid;
            }else if(num < x){
                begin = mid + 1;
            }else if(num > x){
                end = mid - 1;
            }
        }
        
        return (begin + end)/2;
		/*
		that is the hardest part, to find the num that equals with (int)(sqrt(x))
		finally , it will get to begin > end;
		before that:
		
		*/
    }
};

