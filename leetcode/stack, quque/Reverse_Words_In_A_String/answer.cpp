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


class Solution {
public:
    /**the aim of this function is to reverse the string word by word in place
     */
    void reverseWords(string &s) {
       string tempString; /** < words temporaly store in this string */
       stack<string> st; /** <words are stored in this stack. */
       /**Using a foor loop to get all word
        */
        s.push_back(' ');
       for(int i = 0; i < s.size(); i++){
           /**if the letter is space, 
            * push the tempString into the stack and clear it if tempString is not empty.
            */
            if(s[i] == ' '){
                if(tempString.size() > 0){
                    st.push(tempString);
                    tempString.clear();
                }
                /**
                 * neglect all spaces
                 */
                while((i + 1 < s.size()) && s[i + 1] == ' ') i++;
                continue;
            }
            /**if the letter is not space, push it into the string
             */
            else{
                tempString.push_back(s[i]);
            }
       }
       /**push all the words into the original string
        */
        s.clear();
        while(!st.empty()){
            tempString.clear();
            /**get the first word in the stack
             */
            tempString = st.top();
            st.pop();
            /**combine the string
            */
            s = s + tempString;
            if(!st.empty()) s = s + " ";
        }
    }
};
/**
*	add a ' ' to the end of s avoid additional check on this string !
*/
