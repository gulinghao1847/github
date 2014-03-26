/*
Maximal Rectangle Total Accepted: 4118 Total Submissions: 19440 My Submissions
Given a 2D binary matrix filled with 0's and 1's, find the largest rectangle containing all ones and return its area.
*/
class Solution {
public:
    int maximalRectangle(vector<vector<char> > &matrix) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        int maxArea = 0;
        if(matrix.size() == 0 || matrix[0].size() == 0) return maxArea;
        vector<int> height(matrix[0].size() + 1, 0);
        for(int i = 0; i < matrix.size(); i++){
            for(int j = 0; j < matrix[0].size(); j++){
                if(i > 0) height[j] = matrix[i][j] == '1' ? height[j] + 1 : 0;
                else height[j] = matrix[i][j] - '0';
            }
            height[height.size() - 1] = 0;
            int ii = 0;
            stack<int> st;
            while(ii <= height.size()){
                if(st.empty() || height[st.top()] <= height[ii]){
                    st.push(ii++);
                }else{
                    int pos = st.top();
                    st.pop();
                    maxArea = max(maxArea, (st.empty() ? ii : (ii - st.top() - 1)) * height[pos]);
                }
            }
        }
        return maxArea;
    }
};
/*
这里犯了两个错误， 第一个是每次用stack的时候没有clear导致stack里面有数据。。 这是第一点， 第二点是11行的时候， 如果要判断matrix[0]的size必须要看看matrix.size() > 0才行
*/

