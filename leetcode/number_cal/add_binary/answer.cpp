/*
Add Binary Total Accepted: 2248 Total Submissions: 9259 My Submissions
Given two binary strings, return their sum (also a binary string).

For example,
a = "11"
b = "1"
Return "100".
*/
class Solution {
public:
    int getInt(char s){
        return s - '0';
    }
    string addBinary(string a, string b) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        int s1 = a.size();
        int s2 = b.size();
        string res;
        string sm;
        if(s1 > s2){
            res = a;
            sm = b;
        }else{
            res = b;
            sm = a;
        }
        int s3 = res.size();
        int s4 = sm.size();
        int temp = 0;
        int count = s4 - 1;
        for(int i = s3 - 1; i >= 0; i--){
            int n1 = count >= 0 ? getInt(sm[count--]) : 0;
            int n2 = getInt(res[i]);
            if(n1 + n2 + temp >= 2){res[i] = '0' + n1 + n2 + temp - 2;temp = 1;}  //remember to add temp!!!!!!!!
            else {res[i] = '0' + n1 + n2 + temp; temp = 0;}
        }
        if(temp == 1){
            res.insert(0, "1");
        }
        return res;
    }
};
/*
New Version:
*/
class Solution {
public:
    int getInt(char x){
        return x - '0';
    }
    string addBinary(string a, string b) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        string result;
        int i = 0;
        int j = 0;
        int carry = 0;
        int sum = 0;
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        while(i < a.size() || j < b.size()){
            int first = i < a.size() ? getInt(a[i]) : 0;
            int second = j < b.size() ? getInt(b[j]) : 0;
            sum = carry + first + second;
            if(sum >= 2){
                carry = 1;
                sum = sum - 2;
            }else{
                carry = 0;
            }
            result.push_back(sum + '0');
            i++;
            j++;
        }
        if(carry == 1){
            result.push_back('1');
        }
        reverse(result.begin(), result.end());
        return result;
    }
};

