/*
Word Ladder Total Accepted: 5305 Total Submissions: 31981 My Submissions
Given two words (start and end), and a dictionary, find the length of shortest transformation sequence from start to end, such that:

Only one letter can be changed at a time
Each intermediate word must exist in the dictionary
For example,

Given:
start = "hit"
end = "cog"
dict = ["hot","dot","dog","lot","log"]
As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
return its length 5.

Note:
Return 0 if there is no such transformation sequence.
All words have the same length.
All words contain only lowercase alphabetic characters.
*/
class Solution {
public:
    int ladderLength(string start, string end, unordered_set<string> &dict) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        unordered_set<string> explored;
        queue<string> q;
        q.push(start);
        int lvl1 = 1;
        int lvl2 = 0;
        int lvl = 0;
        while(!q.empty()){
            string s = q.front();
            q.pop();
            lvl1--;
            for(int i = 0; i < s.size(); i++){
                for(int j = 0; j < 26; j++){
                    string testString = s;
                    testString[i] = j + 'a';
                    if(testString.compare(end) == 0){
                        return lvl + 2;
                    }
                    if(dict.find(testString) != dict.end() && explored.find(testString) == explored.end()){
                        lvl2++;
                        q.push(testString);
                        explored.insert(testString);
                    }else{
                        continue;
                    }
                }
            }
            if(lvl1 == 0){
                lvl1 = lvl2;
                lvl2 = 0;
                lvl++;
            }
        }
        return 0;
    }
};

