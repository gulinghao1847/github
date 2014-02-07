class Solution {
public:
    int path(vector<vector<int>>& m, int row, int column, vector<vector<int>>& cost){
        if(row < 0 || column < 0 || m[row][column] == 1){
            return 0;
        }
        if(cost[row][column] != -1){
            return cost[row][column];
        }
        int ret = path(m, row, column - 1, cost) + path(m, row - 1, column, cost);
        cost[row][column] = ret;
        return ret;
    }
    
    int uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        int num = 0;
        int s1 = obstacleGrid.size();
        if(s1 == 0) return 0;
        int s2 = obstacleGrid[0].size();
        if(s2 == 0) return 0;
        vector<vector<int>> cost(s1, vector<int>(s2, -1));
        cost[0][0] = 1;
        num = path(obstacleGrid, s1 - 1, s2 - 1, cost);
        return num;
    }
};