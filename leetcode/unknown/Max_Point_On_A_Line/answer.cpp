/*
Max Points on a Line Total Accepted: 5743 Total Submissions: 56462 My Submissions
Given n points on a 2D plane, find the maximum number of points that lie on the same straight line.
*/
/**
 * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 *     Point() : x(0), y(0) {}
 *     Point(int a, int b) : x(a), y(b) {}
 * };
 */
class Solution {
public:
    int maxPoints(vector<Point> &points) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        int maxNum = 0;
        unordered_map<double, int> mp;
        if(points.size() <= 1){
            return points.size();
        }
        for(int i = 0; i < points.size(); i++){
            mp.clear();
            Point x = points[i];
            int same = 1;
            int maxSlope = 0;
            for(int j = i + 1; j < points.size(); j++){
                Point y = points[j];
                double slope = std::numeric_limits<double>::infinity();
                if(x.x == y.x && x.y == y.y){
                    same++;
                }else{
                    if(x.x != y.x){
                        slope = (double)(y.y - x.y)/(double)(y.x - x.x);
                    }
                    if(mp.find(slope) == mp.end()){
                        mp[slope] = 1;
                    }else{
                        mp[slope]++;
                    }
                }
                maxSlope = maxSlope > mp[slope] ?  maxSlope : mp[slope];
            }
            maxNum = maxNum > (maxSlope + same) ? maxNum : maxSlope + same;
        }
        return maxNum;
    }
};

