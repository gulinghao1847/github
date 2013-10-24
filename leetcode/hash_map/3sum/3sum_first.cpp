/*
完全没有考虑duplicate错误的解法
*/
class Solution {
public:
    vector<vector<int> > threeSum(vector<int> &num) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        sort(num.begin(), num.end());
        vector<vector<int>> result;
        vector<int> now(3,0);
        int size = num.size();
        for(int i = 0; i < size; i++){
            int j = i + 1;
            int k = size - 1;
            while(j < k){
                int sum3 = num[i] + num[j] + num[k];
                if(sum3 > 0){
                    k--;
                }else if(sum3 < 0){
                    j++;
                }else{
                    now[0] = num[i];
                    now[1] = num[j];
                    now[2] = num[k];
                    j++;
                    k--;
                    result.push_back(now);
                }
            }
        }
        return result;
    }
};