/*
Best Time to Buy and Sell Stock
Say you have an array for which the ith element is the price of a given stock on day i.

If you were only permitted to complete at most one transaction (ie, buy one and sell one share of the stock), design an algorithm to find the maximum profit.
*/
class Solution {
public:
    int maxProfit(vector<int> &prices) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        int max = 0;
        int minV = INT_MAX;
        int diff = 0;
        for(int i = 0; i < prices.size(); i++){
            if(minV > prices[i]) minV = prices[i];
            diff = prices[i] - minV;
            if(max < diff) max = diff;
        }
        return max;
    }
};