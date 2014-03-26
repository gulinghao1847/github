/*
ZigZag Conversion Total Accepted: 4941 Total Submissions: 22002 My Submissions
The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)

P   A   H   N
A P L S I I G
Y   I   R
And then read line by line: "PAHNAPLSIIGYIR"
Write the code that will take a string and make this conversion given a number of rows:

string convert(string text, int nRows);
convert("PAYPALISHIRING", 3) should return "PAHNAPLSIIGYIR".
*/
class Solution {
public:
    string convert(string s, int nRows) {
        string res;
        if(nRows <= 1){
            return s;
        }
        int sz = s.size();
        int pattern = nRows*2 - 2;
        for(int i = 0; i < nRows; i++){
            int count = i;
            while(count < sz){
                if(i == 0 || i == nRows - 1){
                    res.push_back(s[count]);
                    count = count + pattern;
                }else{
                    res.push_back(s[count]);
                    int pos = pattern - count%pattern + (count/pattern)*pattern;
                    if(pos < sz) res.push_back(s[pos]);
                    count = count + pattern;
                }
            }
        }
        return res;
    }
};


//
/**The aim of this class is to solve the ZigZag Conversion problem
 */
class Solution {
public:
    /**Convert a string to a Zigzag style string, given number of rows
     */
    string convert(string s, int nRows) {
        string result;    /**< return string */
        /**the following for loop convert the originally string to a zigzag style string
         */
         /**if the number of row in this zigzag pattern is lees than 2, return the originally string
          */
         if(nRows < 2) return s;
        int pattern = 2*nRows - 2; /** < number of chars in one cycle in this pattern */
        for(int i = 0; i < nRows; i++){
            /**the first line and the last line has the same pattern,
             * so we group them together
             * Pattern: the first line and the last line will pick a char every nRows chars.
             */
             if(i == 0 || i == nRows){
                 /**using a while loop to get all chars picked by the first line and the last line separately
                  */
                  int size = 0; /** < loop counter */
                  while((size * pattern + i) < s.size()){
                      /**push char to the return string
                       */
                      result.push_back(s[size * pattern +  i]);
                      /**get the position of next char
                       */
                       size = size++;
                  }
             }
             /**for other rows
              */
             else{
                /**using a while loop to get all chars picked by the first line and the last line separately
                 */
                int size = 0; /** < loop counter */
                while((size * pattern + i)< s.size()){
                    /**these rows will pick two chars per cycle
                     */
                    /**push the first char into the result string
                     */
                    result.push_back(s[size * pattern + i]);
                    /**get the second char position
                     * Knowing that (position of the first char plus position of the second char) % (pattern) = 0
                     */
                    int position =  (pattern - i) + size * pattern;
                    /**push the second char into the result string
                     */
                    if(position < s.size() && position != (size * pattern + i)) result.push_back(s[position]);
                    size++;
                }
             }
        }
        return result; /** < return the string */
    }
};

