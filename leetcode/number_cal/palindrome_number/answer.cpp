/*
Palindrome Number Total Accepted: 8141 Total Submissions: 28124 My Submissions
Determine whether an integer is a palindrome. Do this without extra space.

click to show spoilers.

Some hints:
Could negative integers be palindromes? (ie, -1)

If you are thinking of converting the integer to string, note the restriction of using extra space.

You could also try reversing an integer. However, if you have solved the problem "Reverse Integer", you know that the reversed integer might overflow. How would you handle such case?

There is a more generic way of solving this problem.
*/
class Solution {
public:
    bool isPalindrome(int x) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        if(x < 0) return false;
        //reverse this integer
        int var = x;
        int comp = 0;
        while(var > 0){
            comp = comp * 10 + var%10;
            var = var/10;
        }
        return x == comp;
    }
};

