class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        // Note: The Solution object is instantiated only once and is reused by each test case.    
        int size1 = s1.size();
        int size2 = s2.size();
        int size3 = s3.size();
        vector<vector<bool>> matrix(size1 + 1, vector<bool>(size2 + 1,false));//= new matrix();
        matrix[0][0] = true;
        if(size1 + size2 != size3){
            return false;
        }
        //init
        for(int i = 0; i < size1; i++){
            if(s1[i] == s3[i]){
                matrix[i + 1][0] = matrix[i][0];
            }else 
                break;
        }
        for(int i = 0; i < size2; i++){
            if(s2[i] == s3[i]){
                matrix[0][i + 1] = matrix[0][i];
            }else
                break;
        }
        //dp
        for(int i = 0; i < size1; i++){
            for(int j = 0; j < size2; j++){
                if(s1[i] == s3[i + j + 1]){    //since when i = j =0, s3[i + j] has been checked, so we need to check from i + j + 1;
                    if(matrix[i][j+1] == true){    //matrix[i][j+1] means s3[i+j+1-1] 
                        matrix[i+1][j+1] = true;
                    }
                }
                if(s2[j] == s3[i + j + 1]){
                    if(matrix[i+1][j] == true){
                        matrix[i+1][j+1] = true;
                    }
                }
            }
        }
        return matrix[size1][size2];
    }
};