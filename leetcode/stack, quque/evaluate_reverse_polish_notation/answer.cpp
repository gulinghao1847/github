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
class Solution {
public:
    bool isNum(string& a, int& num){
        int i = 0;
        int sign = 1;
        if(a.size() > 1 && (a[0] == '-' || a[0] == '+')){
            i++;
            sign = a[0] == '-' ? -1 : 1;
        }
        for(; i < a.size();i++){
            if(a[i] > '9' || a[i] < '0'){
                return false;
            }
            num = num*10 + a[i] - '0';
        }
        num = num * sign;
        return true;
    }
    
    int doOperation(int a, int b, char& op){
        int res = 0;
        switch(op){
            case '+':res = a + b;
                break;
            case '-':res = b - a;
                break;
            case '/':res = b/a;
                break;
            case '*':res = b*a;
                break;
        }
        return res;
    }
    //assumption: 1. all numbers are valid int
    //            2. all operations are valid
    int evalRPN(vector<string> &tokens) {
        stack<int> s;
        for(int i = 0; i < tokens.size(); i++){
            int num = 0;
            if(isNum(tokens[i], num)){
                s.push(num);
            }else{
                int a = s.top();
                s.pop();
                int b = s.top();
                s.pop();
                int value = doOperation(a, b, tokens[i][0]);
                s.push(value);
            }
        }
        return s.top();
    }
};

