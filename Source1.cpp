#include<fstream>
#include <iostream>
#include<string>
#include<vector>
#include<sstream>
#include<algorithm>
using namespace std;
#define SIZE 2000


//int main()
//{
//	string s;
//	//cin >> s;
//	s = "d:\\Matrix.txt";
//    //cout << "Hello World!\n";
//	Task a;
//	a.readM(s);
//}
class Queue
{
private:
	int* arr; //elements in queue
	int capacity; //max elements 
	int first;
	int last;
	int current;	//current size
public:
	Queue(int size = SIZE);
	~Queue();
	void push_back(int v);
	void pop();
	int front();
	int back();
	bool empty();
	int size();
	bool full();

};
Queue::Queue(int size)
{
	arr = new int[size];
	capacity = size;
	first = 0;
	current = 0;
	last = -1;

}
Queue::~Queue()
{
	delete arr;
}
void Queue::push_back(int v)
{

	if (full())
	{
		exit(EXIT_FAILURE);
	}
	last++;
	arr[last] = v;

	current++;
}
int Queue::front()
{
	if (empty())
	{
		exit(EXIT_FAILURE);
	}
	return arr[first];
}
int Queue::back()
{
	if (empty())
	{
		exit(EXIT_FAILURE);
	}
	return arr[last];
}
bool Queue::empty()
{

	return size() == 0;
}
void Queue::pop()
{
	for (int i = 0; i < capacity; i++)
	{
		arr[i] = arr[i + 1];
	}
	current--;
}
int Queue::size()
{
	return current;
}
bool Queue::full()
{
	return size() == capacity;
}

class Task
{
public:
	string readM(string s);
	//void Algorithm(string p);
};

string Task::readM(string s)
{
	ifstream file;
	file.open(s);
	char o;
	int count = 0, count1 = 0;
	string p;

	while (file.get(o))
	{
		if (o == 'X')
		{
			count++;
		}
		if (o == ' ')
		{
			count1++;
		}
		p.push_back(o);

	}
	cout << p << endl;
	cout << "Number of X: " << count << endl;
	cout << "Number of SPACES: " << count1 << endl;

	file.close();
	return p;
}

//void Task::Algorithm(string p)
//{
//
//}

int main()
{
	string s;
	/*cin >> s;
	s += ".txt";*/
	s = "Matrix.txt";
	Task a;
	string y = a.readM(s);
	Queue b(200);


}