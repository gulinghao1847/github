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

//The fourth condition else if(newInterval.end() > interval[i].end) may make this function become n^2, erase function take O(n) time.So we should avoid this. so we creat a new vector
class Solution {
public:
    vector<Interval> insert(vector<Interval> &intervals, Interval newInterval) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        
        vector<Interval> res;
        bool isLarge;
        vector<Interval> :: iterator it=intervals.begin();
        for(;it!=intervals.end();it++)
        {
            if(it->end<newInterval.start)
            {
                res.push_back(*it);
                continue;
            }
            else if(it->start>newInterval.end)
            {
                if(isLarge)
                {
                    res.push_back(newInterval);
                    isLarge=false;
                }
                res.push_back(*it);
                continue;
            }
            newInterval.start= newInterval.start>it->start? it->start:newInterval.start;
            newInterval.end= newInterval.end>it->end? newInterval.end : it->end;
        }
        if(isLarge)
        res.push_back(newInterval);
        return res;
    }
};