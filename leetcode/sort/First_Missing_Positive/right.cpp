/*
例子｛2,1｝
在10－13 行中， 如果对A[i]的值进行存储， 那么会死循环， 因为进行到13行的时候, 新的A[i] - 1 肯定不等于老的 A[i] - 1， 因为a[i]已经变了值 
*/
class Solution {
public:
    int firstMissingPositive(int A[], int n) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        for(int i = 0; i < n; i++){
            if(A[i] <= 0 || A[i] > n || (A[i] - 1 == i) || (A[A[i] - 1] == A[i])) continue;
            int temp = A[i];
            A[i]  = A[A[i] - 1];
            A[A[i] - 1] = temp;
            i--;
        }
        int i;
        for(i = 0; i < n; i++){
            if(A[i] - 1 != i) break;
        }
        return i + 1;
    }
};