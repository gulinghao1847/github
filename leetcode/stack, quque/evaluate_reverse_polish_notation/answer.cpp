/*
Evaluate Reverse Polish Notation Total Accepted: 7012 Total Submissions: 37172 My Submissions
Evaluate the value of an arithmetic expression in Reverse Polish Notation.

Valid operators are +, -, *, /. Each operand may be an integer or another expression.

Some examples:
  ["2", "1", "+", "3", "*"] -> ((2 + 1) * 3) -> 9
  ["4", "13", "5", "/", "+"] -> (4 + (13 / 5)) -> 6
*/
/*
这题目基本思路就是建立一个stack， 然后如果遇到数字就push进去stack， 如果是运算符， 就pop出前两个数字， 然后进行运算， 并把结果push进入stack中， 如此循环， 直到结束，这里要注意在判定string是否是数字的时候， 要判断数字的sign
当sign是＋ 和－的时候会和运算符冲突， 所以要避免这个东西*/

//calculate number from a char string: 1.sign? 2.overflow? 3.char to int?
class Solution {
public:
    int cal(int a, int b, char c){
        int result = 0;
        switch(c){
            case '+':
                    result = a + b;
                    break;
            case '-':
                    result = a - b;
                    break;
            case '*':
                    result = a * b;
                    break;
            case '/':
                    result = a / b;
                    break;
        }
        return result;
    }
    
    //since it is string, so we need to change it to number
    bool getNum(string& a, int& num){
        //sign
        //neglect all space
        int i = 0;
        bool isPos = true;
        bool isSign = true;
        while(a[i] == ' ')i++;
        if(a[i] == '+' || a[i] == '-') {
            isPos = a[i] == '+' ? true : false;
            i++;
        }
        while(a[i] >= '0' && a[i] <= '9') {
            num = num * 10 + a[i] - '0';
            isSign = false;
            i++;
        }
        //assume it is int
        num = isPos ? num : -num;
        return !isSign;
    }
    
    
    int evalRPN(vector<string> &tokens) {
        stack<int> st;
        //assumption: n
        for(int i = 0; i < tokens.size(); i++){
            int num = 0;
            if(getNum(tokens[i], num)){
                st.push(num);
            }else{
                int a = st.top();
                st.pop();
                int b = st.top();
                st.pop();
                int c = cal(b, a, tokens[i][0]);
                st.push(c);
            }
        }
        return st.top();
    }
};

