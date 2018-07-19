#include <stdio.h>
#include <Windows.h> 
#include <iostream>
#include <functional>
#include <unordered_map>

using namespace std; 

class Test {
public:
	void Add(int a, int b);
	void Delete(int c, int d); 
	void Mult(int c, int d);
	void init();
	void RunMap(int index);
private:
 	std::unordered_map<int, void(Test::*)(int, int)> m_FuncMaps;
	std::unordered_map<int, function<void(int, int)>> m_FuncMaps2; 
};

void Test::init()
{
	m_FuncMaps[1] = &Test::Add;
	m_FuncMaps[2] = &Test::Delete;
 	m_FuncMaps2[3] = bind(&Test::Mult, this, placeholders::_1, placeholders::_2);  //方法2
} 
void Test::Mult(int c, int d)
{
	printf("is Mult\n");
}
void Test::Add(int a, int b)
{
	printf("is Add\n");
}
void Test::Delete(int a, int b)
{
	printf("is Delete\n");
}

void Test::RunMap(int index)
{
	auto funcIter = m_FuncMaps.find(index);
	if (funcIter != m_FuncMaps.end())  //方法1
	{
		printf("method A-");
		(this->*funcIter->second)(1, 1);
	}
	auto funcIter2 = m_FuncMaps2.find(index);
	if (funcIter2 != m_FuncMaps2.end())  //方法2
	{
		printf("method B-");
		(funcIter2->second)(1, 1);
	} 
}
 
void main() 
{
	Test test;
	test.init();
	test.RunMap(1);
	test.RunMap(2);
	test.RunMap(3);
	getchar(); 
}

 