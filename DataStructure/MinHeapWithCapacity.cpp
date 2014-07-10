#include <iostream>
#include <vector>
#include <string>
using namespace std;


class MinHeap{
private:
    int size;
    int capacity;
    vector<int> array;
    void bubbleUp(int index);
    int leftChild(int index);
    int rightChild(int index);
    int parent(int index);
    void bubbleDown(int index);
public:
    MinHeap(int);
    ~MinHeap();
    void push(int val);
    int top();
    void pop();
};

MinHeap::MinHeap(int capacity){
    size = 0;
    this -> capacity = capacity;
}
MinHeap::~MinHeap(){}

int MinHeap::top(){
    if(size == 0) return -1;
    return array[0];
}

void MinHeap::push(int val){
    if (size < capacity) {
        array.push_back(val);
        size++;
        bubbleUp(size - 1);
    }else{
        if(val < array[0]){
            //do nothing
        }else{
            array[0] = val;
            bubbleDown(0);
        }
    }
}

int MinHeap::leftChild(int index){
    index++;
    int result = index * 2;
    if(result > size){
        return -1;
    }
    return result - 1;
}

int MinHeap::rightChild(int index){
    index++;
    int result = index * 2 + 1;
    if(result > size){
        return -1;
    }
    return result - 1;
}

int MinHeap::parent(int index){
    if(index == 0 || index >= size) return -1;
    index++;
    return index / 2 - 1;
}

void MinHeap::bubbleUp(int index){
    if(index <= 0) return;
    int smaller = array[index];
    //cout << "smaller : " << index << endl;
    while (index > 0) {
        int pare = parent(index);
        //cout << "pare:  " << pare << endl;
        smaller = array[index];
        if(smaller < array[pare]){
            smaller = array[pare];
            array[pare] = array[index];
            array[index] = smaller;
            index = pare;
        }else{
            break;
        }
    }
}

void MinHeap::bubbleDown(int index){
    while (index < size) {
        int localIndex = -1;
        int value = INT_MAX;
        int left = 0;
        int right = 0;
        //cout << index << endl;
        if((left = leftChild(index)) != -1){
            localIndex = left;
            value = array[left];
        }
        //cout << left << endl;
        //cout << localIndex << endl;
        //cout << value << endl;
        if((right = rightChild(index)) != -1 && array[right] < value){
            localIndex = right;
            value = array[right];
        }
        if(localIndex != -1 && array[index] > value){
            array[localIndex] = array[index];
            array[index] = value;
            index = localIndex;
        }else{
            break;
        }
    }
}

void MinHeap::pop(){
    if(size == 0) return;
    array[0] = array[size - 1];
    size--;
    bubbleDown(0);
}

int main(){
    MinHeap test(2);
    test.push(7);
    cout << test.top() << endl;
    test.push(8);
    cout << test.top() << endl;
    test.push(9);
    cout << test.top() << endl;
    test.push(10);
    cout << test.top() << endl;
    test.pop();
    cout << test.top() << endl;
    test.pop();
    cout << test.top() << endl;
    /*
    test.pop();
    cout << test.top() << endl;
    test.pop();
    cout << test.top() << endl;
     */
}

