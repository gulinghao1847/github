class Solution {
public:
    bool wordBreak(string s, unordered_set<string> &dict) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        int size = s.size();
        vector<bool> matrix(size + 1, false);
        int len = 0;
        matrix[0] = true;
        
        unordered_set<string>::iterator it;
        for(int i = 1; i <= size; i++){
            for(int j = 0; j< i ; j++){
                if(matrix[j]== true){
                    len = i - j;
                    it = dict.find(s.substr(j,len));
                    if(it != dict.end()){
                        matrix[i] =  true;
                        break;
                    }
                }
            }
        }
        return matrix[size];
    }
};