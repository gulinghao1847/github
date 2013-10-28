class Solution {
public:
    int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        int size = gas.size();
        for(int i = 0; i < size; i++){
            vector<int> matrix(size, 0);
            if(i == size - 1){
                matrix[0] = gas[i] - cost[i];
            }else{
                matrix[i + 1] = gas[i] - cost[i];
            }
            for(int j = 0; j < size; j++){
                int des = ((i + j + 1)/size == 0)?(i + j + 1) : (i + j + 1)%size;  //question?
                int pre = (des - 1) < 0 ? (size - 1) : (des - 1);
                matrix[des] = matrix[pre] + gas[pre] - cost[pre];
                if (matrix[des] < 0) {
                    if(des = i + 1){
                        i = i + 1;
                    }else{
                        i =  des - 1;
                    }
                    break;
                }
                //cout<<"des:"<<des + 1<<"----pre:"<<pre + 1<<endl;
                if(des == i && matrix[des] >= 0){
                    return i + 1;
                }
            }
        }
        return -1;
    }
};