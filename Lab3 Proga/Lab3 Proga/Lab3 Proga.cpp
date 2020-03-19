#include<fstream>
#include <iostream>
#include<string>
#include<vector>
#include<sstream>
#include<algorithm>
using namespace std;
#define SIZE 2000

class Queue
{
private:
	int* arr; //elements in queue
	int capacity; //max elements 
	int first;
	int last;
	int current;	//current size
public:
	Queue(int size=SIZE);
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
	last =-1;

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
	
	return size()==0;
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
	return size()==capacity;
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
	cout <<"Number of X: "<< count << endl;
	cout <<"Number of SPACES: "<< count1 << endl;
	
	file.close();
	return p;
}

int main()
{
	string fff="";
	ifstream file("input.txt");
	int k = 0;
	getline(file, fff);
	int kk = fff.size()/2+1;
	while (fff!="maxloh")
	{
		fff = "maxloh";
		getline(file, fff);
		k++;
	}
	int **mm = new int *[k];
	for(int i=0; i<k; i++) mm[i] = new int [kk];
	file.close();
	file.open("input.txt");

	int ss=0;
	for (int i = 0; i < k; i++)
	{
		getline(file, fff);
		for (int j = 0; j < kk*2-1; j+=2)
		{
			if (fff[j] == ' ' && fff[j + 1] == ' ') { ss++; mm[i][j / 2] = ss; }
			else mm[i][j / 2] = 0;
		}
	}
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < kk; j++)
		{
			cout << " \t" << mm[i][j];
		}
		cout << "\n";
	}

	int** ms = new int* [ss+1];
	for (int i = 0; i < ss+1; i++) ms[i] = new int[ss+1];

	for (int i = 1; i < ss; i++)
	{
		for (int j = 1; j < ss; j++)
		{
			ms[i][j] = 0;
		}
	}

	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < kk; j++)
		{
			if (mm[i][j] >= 1)
			{
				if (i - 1 >= 0) if (mm[i - 1][j] >= 1) { ms[mm[i - 1][j]][mm[i][j]]=1; ms[mm[i][j]][mm[i - 1][j]]=1; }
				if (j - 1 >= 0) if (mm[i][j - 1] >= 1) { ms[mm[i][j-1]][mm[i][j]]=1; ms[mm[i][j]][mm[i][j-1]]=1; }
				if (i + 1 < k) if (mm[i + 1][j] >= 1) { ms[mm[i + 1][j]][mm[i][j]]=1; ms[mm[i][j]][mm[i + 1][j]]=1; }
				if (j + 1 < kk) if (mm[i][j + 1] >= 1) { ms[mm[i][j+1]][mm[i][j]]=1; ms[mm[i][j]][mm[i][j+1]]=1; }
			}
		}
	}

	for (int i = 1; i < ss; i++)
	{
		cout << "\n";
		for (int j = 1; j < ss; j++)
		{
			cout << ms[i][j] << " ";
		}
	}
	//or(int i=1; i<)
	//string s;
	/*cin >> s;
	s += ".txt";*/
	//s = "Matrix.txt";
	//Task a;
	//string y=a.readM(s);
	//Queue b(200);
}