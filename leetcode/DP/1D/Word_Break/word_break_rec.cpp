class Solution {
    bool** matrix;
public:
    bool run(string& s, unordered_set<string>& dict, int pos){
        int size = s.size();
        bool ret = false;
        int begin = pos;
        for(int i = pos; i < size; i++){
            string myS(s.begin() + begin, s.begin() + i);
            unordered_set<string>::iterator it = dict.find(myS);
            if(it == dict.end()){
                continue;
            }else{
                if(i == size - 1){
                    ret = true;
                }else{
                    ret = run(s,dict,i + 1);
                }
            }
        }
        return ret;
    }
    
    bool wordBreak(string s, unordered_set<string> &dict) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        if(s.size() == 0){
            return true;
        }
        int size = s.size();
        
        matrix=(bool**)malloc(sizeof(bool*)*size);
        for(int i = 0; i < size; i++){
            matrix[i] = (bool*)malloc(sizeof(bool)*size);
            for(int j = 0; j < size; j++){
                matrix[i][j] = false;
            }
        }
        
        bool ret = run(s, dict, 0);
        return ret;
    }
};