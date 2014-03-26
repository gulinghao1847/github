#define int ELETYPE
class TagStack{
private:
	int size;
	int top;
	int capacity;
	//vector<ELETYPE>* stackArray;
public:
	virtual ELETYPE top() = 0;
	virtual void pop() = 0;
	virtual void push(ELETYPE) = 0;
	TagStack(int);
};

class ArrayStack{
private:
	vector<ELETYPE>* stackArray;
public:
	ArrayStack(int);
	//ArrayStack(const ArrayStack&);
	ELETYPE top();
	void pop();
	void push(ELETYPE);
};

