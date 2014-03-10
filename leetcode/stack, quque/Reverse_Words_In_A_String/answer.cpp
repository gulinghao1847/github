/*
Reverse Words in a String Total Accepted: 1145 Total Submissions: 7494 My Submissions
Given an input string, reverse the string word by word.

For example,
Given s = "the sky is blue",
return "blue is sky the".

click to show clarification.

Clarification:
What constitutes a word?
A sequence of non-space characters constitutes a word.
Could the input string contain leading or trailing spaces?
Yes. However, your reversed string should not contain leading or trailing spaces.
How about multiple spaces between two words?
Reduce them to a single space in the reversed string.
*/
class Solution {
public:
    void reverseWords(string &s) {
        stack<char> st;
        string comp = s;
        int size = s.size();
        s.clear();
        for(int i = comp.size() - 1; i >= 0;){
            if(comp[i] != ' '){
                st.push(comp[i]);
                i--;
            }else{
                int num = 0;
                while(!st.empty()){
                    s.push_back(st.top());
                    st.pop();
                    num++;
                }
                while(comp[i] == ' ') i--;
                if(num != 0 && i >= 0){
                    s.push_back(' ');
                }
            }
        }
        while(!st.empty()){
            s.push_back(st.top());
            st.pop();
        }
    }
};

