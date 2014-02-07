/*
Climbing Stairs Total Accepted: 6088 Total Submissions: 18617 My Submissions
You are climbing a stair case. It takes n steps to reach to the top.

Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
*/
class Solution {
public:
    int climbStairs(int n) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        vector<int> steps(n, 0);
        
        steps[n - 1] = 1;
        steps[n - 2] = 2;
        if(n <= 2) 
            return steps[0];
        for(int i = n - 3; i >=0; i--){
            steps[i] = steps[i + 1] + steps[i + 2];
        }
        return steps[0];
    }
};

