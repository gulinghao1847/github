class Solution {
public:
    void run(vector<vector<int>>& result, vector<int>& now, int sum, int target, int begin, vector<int>& num){
        if(sum == target){
            result.push_back(now);
            return;
        }
        int size = num.size();
        for(int i = begin; i < size; i++){
            sum = sum + num[i];
            if(sum > target) 
                return;
            now.push_back(num[i]);
            run(result, now, sum, target, i + 1, num);
            now.pop_back();
            sum = sum - num[i];
            while(i != size - 1 && num[i + 1] == num[i]) i++;
        }
    }
    
    vector<vector<int> > combinationSum2(vector<int> &num, int target) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        vector<vector<int>> result;
        vector<int> now;
        sort(num.begin(), num.end());
        //int size = num.size();
        run(result, now, 0, target,0, num);
        return result;
    }
};