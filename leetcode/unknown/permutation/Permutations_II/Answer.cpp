/**
Permutations II Total Accepted: 1445 Total Submissions: 5606 My Submissions
Given a collection of numbers that might contain duplicates, return all possible unique permutations.

For example,
[1,1,2] have the following unique permutations:
[1,1,2], [1,2,1], and [2,1,1].
 */
class Solution {
public:
    void run(vector<vector<int>>& result, vector<int>& now, vector<int>& used, int number, vector<int> &num){
        int size = num.size();
        if(number == size){
            result.push_back(now);
            return;
        }
        for(int i = 0; i < size; i++){
            if(used[i] == 1) continue;
            used[i] = 1;
            int org = i;
            while(i < size - 1 && num[i] == num[i + 1]) i++;
            now.push_back(num[i]);
            run(result, now, used, number + 1, num);
            now.pop_back();
            used[org] = 0;
        }
    }
    vector<vector<int> > permuteUnique(vector<int> &num) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        int size = num.size();
        sort(num.begin(), num.end());
        vector<int> used(size, 0);
        vector<vector<int>> result;
        vector<int> now;
        run(result, now, used, 0, num);
        return result;
    }
};
/*
 感觉本题非常经典， 虽然和I 只有一点差距， 如果按照原来的算法， 也只需要增加line： 21 就可以了， 但这里就会产生一个bug， 就是每次的num［i］都会是最后一个相等的数， 导致在整个排列中， 相同的数至多只能存在一个，
这里， 我用了19,20 行来解决问题， 这里， 代码顺序无法改变， 否则会出错， 要注意
*/