class Solution {
public:
    bool check(string s){
        int size = s.size();
        int begin = 0;
        int end = size - 1;
        while(begin <= end){
            if(s[begin] != s[end]){
                return false;
            }
            begin++;
            end--;
        }
        return true;
    }
    
    void run(string& s, int begin, int& num){
        int size = s.size();
        int last = 0;
        if(begin == size){
            num--;
            return;
        }
        
        for(int i = begin; i < size; i++){
            if(check(s.substr(begin, i - begin + 1))){
                last = i;
            }
        }
        
        int next = last + 1;
        num++;
        run(s, next, num);
    }
    int minCut(string s) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        int num = 0;
        run(s, 0, num);
        return num;
    }
};