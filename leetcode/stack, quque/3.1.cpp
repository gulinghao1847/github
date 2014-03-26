//const int MAX_STACK_SIZE = 100;
template <class elementType>
class myStack{
private:
	//int size;   //capacity of the stack
	int start;
	static vector<elementType>* array //use an int vector to store the data set
    int top; //the position of the top element
public:
	//top function for stack
	elementType virtual top() = 0; 
	//push function for stack
	void virtual push(elementType x) = 0;
	//pop function for stack
	void virtual pop() = 0;
	myStack(elementType x);
};
//In the implemention, we need to create three different stack class
//first stack
//first stack just like normal stack, begins at the head.
template <class elementType>
class FirstStack: public myStack{
public:
	FirstStack(elementType x);
};

//second stack begins at the end of the array, going to the begin
template <class elementType>
class SecondStack: public myStack{
public:
	SecondStack(elementType x);
};

//third stack begins in the middle of the array, going right 
//since we need to shift this stack sometimes, so the start position of this stack is not fixed, so we need a variable to record the beginning position
template <class elementType>
class ThirdStack : public myStack{
public:
	ThirdStack(elementType x);
};

myStack::myStack(elementType x){
	start = x;
	top = x;
}
void FirstStack::FirstStack():



