/*
Recover Binary Search Tree Total Accepted: 4609 Total Submissions: 20997 My Submissions
Two elements of a binary search tree (BST) are swapped by mistake.

Recover the tree without changing its structure.

Note:
A solution using O(n) space is pretty straight forward. Could you devise a constant space solution?
confused what "{1,#,2,3}" means? > read more on how binary tree is serialized on OJ.
*/
class Solution {
public:
    void run(vector<string>& result,string& s, string& now, int begin, int num){
        int s1 = s.size();
        int s2 = now.size();
        num++;
        if(num > 4) return;
        if((s1 - begin - (5 - num)) < 0) return;
        if(s1 - begin - 3*(5 - num) > 0) return;
        
        for(int i = begin; i < begin + 3; i++){
            int number = atoi(s.substr(begin, i - begin + 1).c_str());
            if(number > 255) continue;
            //num++;
            if(now.size()!=0) now = now + ".";
            int size = now.size();
            now = now + s.substr(begin, i - begin + 1);
            if(num == 4 && i = s1 - 1){
                int test = atoi(s.substr(s.begin() + i + 1, s.end() - 1).c_str());
                if(test <=255){
                    result.push(now);
                }
                continue;
            }
            run(result, s, now, i + 1, num);
            now.erase(size, i - begin + 2);
        }
    }
    vector<string> restoreIpAddresses(string s) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        int size = s.size();
        if(size < 4 || size > 12) return;
        vector<string> result;
        string now;
        run(result, s, now, 0, 0);
        return result;
    }
};

