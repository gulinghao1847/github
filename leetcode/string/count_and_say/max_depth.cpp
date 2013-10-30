/**
Count and Say Total Accepted: 1216 Total Submissions: 4771 My Submissions
The count-and-say sequence is the sequence of integers beginning as follows:
1, 11, 21, 1211, 111221, ...

1 is read off as "one 1" or 11.
11 is read off as "two 1s" or 21.
21 is read off as "one 2, then one 1" or 1211.
Given an integer n, generate the nth sequence.

Note: The sequence of integers will be represented as a string.
 */
class Solution {
public:
    string countAndSay(int n) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        string count = "1";
        string say = "1";
        while(n > 1){
            count = say;
            say.clear();
            int size = count.size();
            int len = 0;
            char num = NULL;
            for(int i = 0; i < size;){
                len = 1;
                num = count[i++];
                while(count[i] == num) {len++;i++;}
                say.push_back((char)('0' + len));
                say.push_back(num);
            }
            n--;
        }
        return say;
    }
};