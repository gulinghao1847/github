class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        int num = 0;
        int s1 = obstacleGrid.size();
        if(s1 == 0) return 0;
        int s2 = obstacleGrid[0].size();
        if(s2 == 0) return 0;
        vector<vector<int>> cost(s1, vector<int>(s2, 0));
        //init
        cost[0][0] = (obstacleGrid[0][0] == 0)?1:0;

        for(int i = 1; i < s1; i++){
            if(obstacleGrid[i][0] == 1) break;
            cost[i][0] = cost[i - 1][0];
        }
        for(int i = 1; i < s2; i++){
            if(obstacleGrid[0][i] == 1) break;
            cost[0][i] = cost[0][i - 1];
        }
        
        //bottom to top
        for(int i = 1; i < s1; i++){
            for(int j = 1; j < s2; j++){
                if(obstacleGrid[i][j] == 1){
                    cost[i][j] = 0;
                }else{
                    cost[i][j] = cost[i - 1][j] + cost[i][j - 1];
                }
            }
        }
        return cost[s1 - 1][s2 - 1];
    }
};