#include <iostream>
#include <string>
#include <time.h>
class Student{
private:
	std::string stuName;
	int stuID;
	static int IDGen;
public: 
	Student(std::string stuName);
	Student(const Student&);
};

int Student::IDGen = 0;
Student::Student(std::string name){
	stuName = name;
	stuID = ++IDGen;
}

Student::Student(const Student& student){
	stuName = student.stuName;
	stuID = student.stuID;
}

string Student::getName(){
	return stuName;
}

int Student::getStuID(){
	return stuID;
}

class Test{
private:
	std::string testName;
	time_t testTime;
public:
	Test(const Test&);
	Test(time_t time, std::string testName);
	std::string getTestName();
	time_t getTestTime();
};

Test::Test(const Test& newTest){
	testTime = newTest.testTime;
	testName = newTest.testName;
}

Test::Test(time_t time, std::string name){
	testTime = time;
	testName = name;
}

std::string getTestName(){
	return testName;
}

time_t testTime(){
	return testTime;
}
















