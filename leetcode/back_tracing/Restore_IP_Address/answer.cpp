/*
Restore IP Addresses Total Accepted: 1809 Total Submissions: 9244 My Submissions
Given a string containing only digits, restore it by returning all possible valid IP address combinations.

For example:
Given "25525511135",

return ["255.255.11.135", "255.255.111.35"]. (Order does not matter)
*/
//justity the valid value is the hardest part
class Solution {
public:
    void run(vector<string>& res, string& s, int start, string& now, int lvl){
        int size = s.size();
        if(lvl == 3){
            if(size - start > 3 || (size - start == 3 && s[start] > '2') || (size - start == 3 && s[start] == '2' && s.substr(size - 2, 2).compare("55") > 0) || size == start || s[start] == '0' && s.substr(start, size - start).compare("0") != 0) return;
            now = now + s.substr(start, size - start);
            res.push_back(now);
            //cout<<now<<endl;
            for (int i = 0; i < size - start; i++) {
                now.pop_back();
            }
            return;
        }
        //back-tracing
        //lvl++
        for(int i = 1; i <= 3; i++){
            if(start + i > size) continue;
            if((i == 3 && s[start] > '2') || (i == 3 && s[start] == '2' && s.substr(start + 1, 2).compare("55") > 0) ||s[start] == '0' && s.substr(start, i).compare("0") != 0) continue;
            now = now + s.substr(start, i);
            now = now + '.';
            run(res, s, start + i, now, lvl + 1);
            for(int j = 0; j < i + 1; j++){
                now.pop_back();
            }
        }
    }
    vector<string> restoreIpAddresses(string s) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        int size = s.size();
        vector<string> res;
        string now;
        if(size < 4 || size > 16) return res;
        run(res, s, 0, now, 0);
        return res;
    }
};