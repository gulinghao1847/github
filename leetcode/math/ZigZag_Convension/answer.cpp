/*
ZigZag Conversion Total Accepted: 4941 Total Submissions: 22002 My Submissions
The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)

P   A   H   N
A P L S I I G
Y   I   R
And then read line by line: "PAHNAPLSIIGYIR"
Write the code that will take a string and make this conversion given a number of rows:

string convert(string text, int nRows);
convert("PAYPALISHIRING", 3) should return "PAHNAPLSIIGYIR".
*/
class Solution {
public:
    string convert(string s, int nRows) {
        string res;
        if(nRows <= 1){
            return s;
        }
        int sz = s.size();
        int pattern = nRows*2 - 2;
        for(int i = 0; i < nRows; i++){
            int count = i;
            while(count < sz){
                if(i == 0 || i == nRows - 1){
                    res.push_back(s[count]);
                    count = count + pattern;
                }else{
                    res.push_back(s[count]);
                    int pos = pattern - count%pattern + (count/pattern)*pattern;
                    if(pos < sz) res.push_back(s[pos]);
                    count = count + pattern;
                }
            }
        }
        return res;
    }
};

