#include "stack.h"
#include <iostream>
//implementation for the abstract class
TagStack::TagStack(int sz){
	size = 0;
	top = -1;
	capacity = sz;
}

//stack implemntation using array as the container
ArrayStack::ArrayStack(int sz):TagStack(sz){
	stackArray = new vector(sz, 0);
}

//if this stack is empty, return NULL
//else return the top value
ELETYPE ArrayStack::top(){
	if(top < 0){
		std::cout<<"this stack is now empty"<<std::endl;
		return NULL;
	}
	return stackArray[top];
}

//if this stack is empty, print error then do nothing
//else pop the top value and top--
void ArrayStack::pop(){
	if(top < 0){
		std::cout<<"this stack is now empty"<<std::endl;
		return;
	}
	top--;
	size--;
	return;
}

//if size equals to capacity, then we cant push element into this stack anymore
void ArrayStack::push(ELETYPE x){
	if(size == capacity){
		std::cout<<"full"<<std::endl;
		return;
	}
	stackArray[++top] = x;
	size++;
}