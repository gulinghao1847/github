/*
Max Points on a Line Total Accepted: 6053 Total Submissions: 59808 My Submissions
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
    /** the aim of this function is to find max points that lie on the same straight line
     */
    int maxPoints(vector<Point> &points) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        int maxValue = 0;   /** < max value that will be returned */
        /**slope equation: k = (y1 - y2)/(x1 - x2)  &&  x1 - x2 != 0
         */
        /**In order to find max points that lie on the same straight line, we should pick a points first,
         * then get the slope between this points and every node behind it in the vector
         */
         unordered_map<double, int> mp; /** < map the slope to the number of points that have the same slope with the given points */
        for(int i = 0; i < points.size(); i++){
            int same = 1;    /** <get the number of node that is identical with the seleted point  */
            int maxV = 0;    /** < maximum number of node in a straight line except i and points that are identical with i */
            for(int j = i + 1; j < points.size(); j++){
                /**if i and j are identical
                 */
                if(points[i].x == points[j].x && points[i].y == points[j].y){
                    same++;
                }
                /** if they are not identical
                 */
                else{
                    //declare slope and set its initial value to infinity
                    double slope = std::numeric_limits<double>::infinity();
                    /**if i.x != j.x, slope = k = (y1 - y2)/(x1 - x2)
                     * else slope = infinity
                     */
                    if(points[i].x != points[j].x){
                        slope = (double)(points[j].y - points[i].y)/(double)(points[j].x - points[i].x);
                    }
                    /**if we can not find this slope in the hash map, set its value to 1
                     * else value++
                     */
                    if(mp.find(slope) == mp.end()){
                        mp[slope] = 1;
                    }else{
                        mp[slope]++;
                    }
                    /**update maxV
                     */
                    maxV = max(maxV, mp[slope]);
                }
            }
            mp.clear();
            /**update maxValue
             */
            maxValue = max(maxValue, maxV + same);
        }
        return maxValue;
    }
};

