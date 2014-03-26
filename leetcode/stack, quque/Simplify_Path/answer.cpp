/*
Simplify Path Total Accepted: 4348 Total Submissions: 23014 My Submissions
Given an absolute path for a file (Unix-style), simplify it.

For example,
path = "/home/", => "/home"
path = "/a/./b/../../c/", => "/c"
click to show corner cases.

Corner Cases:
Did you consider the case where path = "/../"?
In this case, you should return "/".
Another corner case is the path might contain multiple slashes '/' together, such as "/home//foo/".
In this case, you should ignore redundant slashes and return "/home/foo".
*/
class Solution {
public:
    string simplifyPath(string path) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        string result("");
        int count = 0;
        stack<string> st;
        while(count < path.size()){
            while(path[count] == '/') count++;
            int begin = count;
            while(count < path.size() && path[count] != '/')count++;
            string pathName = path.substr(begin, count - begin);
            //if we encounter '.', do nothing
            if(pathName == ".") continue;
            //if we encounter '..' pop up the first element in this stack
            else if(pathName == ".." && !st.empty()) st.pop();
            //if not , just push this element into the stack
            else if(pathName.size() > 0 && pathName != "..") st.push(pathName);
        }
        while(!st.empty()){
            result = "/" + st.top() + result;
            st.pop();
        }
        if(result.size() == 0){
            result.push_back('/');
        }
        return result;
    }
};

