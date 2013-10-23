/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
public:
    vector<Interval> insert(vector<Interval> &intervals, Interval newInterval) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        //int size = intervals.size();
        for(int i = 0; i < intervals.size(); i++){
            if(newInterval.end < intervals[i].start){
                intervals.insert(intervals.begin() + i, newInterval);
                return intervals;
            }else if(newInterval.end <= intervals[i].end){
                intervals[i].start = newInterval.start < intervals[i].start ? newInterval.start : intervals[i].start;
                return intervals;
            }else if(newInterval.start > intervals[i].end){
                continue;
            }
            else if(newInterval.end > intervals[i].end){
                newInterval.start = newInterval.start < intervals[i].start ? newInterval.start : intervals[i].start;
                newInterval.end = newInterval.end > intervals[i].end ? newInterval.end : intervals[i].end;
                intervals.erase(intervals.begin() + i);
                i--;
                continue;
            }
        }
        intervals.insert(intervals.end(), newInterval);
        return intervals;
    }
};