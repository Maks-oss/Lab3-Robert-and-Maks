#include<fstream>
#include <iostream>
#include<string>
#include<utility>
#include<vector>
#include<cmath>
char symb(int N);
using namespace std;
#define SIZE 2000
void swap(int &t, int &k) { int temp = t; t = k; k = temp; }
int h(int x, int y, int** ms, int k, int kk);
void Adjance(int** mm, int k, int kk, int** ms);
void A_star(int ss, int** ms, vector<int>& c, int x, int y, int** mm, int k, int kk);
void file_out(vector<int>& c, int** mm, int k, int kk);

struct Node
{
	int start, end;
};
class Queue
{
private:
	int* arr; //elements in queue
	int capacity; //max elements 
	int current;//current size

public:
	Queue(int size = SIZE);
	void push(int v);
	void decrease(int last, int val);
	int deletemin();
	void heapify(int small);
	int getmin() { return arr[0]; }
	bool empty() { return current == 0; }
	int size() { return current; }
	bool getel(int ll);
}
Queue::Queue(int size)
{
	arr = new int[size];
	capacity = size;
	current = 0;

}
void Queue::push(int v)
{
	int i = current;
	arr[i] = v;
	current++;
	
	while (i != 0 && arr[(i - 1) / 2] > arr[i])
	{
		swap(arr[i], arr[(i-1)/2]);
		i = (i-1)/2;
	}
}

void Queue::decrease(int last, int val)
{
	arr[last] = val;
	while (last != 0 && arr[(last - 1) / 2] > arr[last])
	{
		swap(arr[last], arr[(last - 1) / 2]);
		last = (last - 1) / 2;
	}
}

void Queue::heapify(int small)
{
	int l = (2 * small) + 1;
	int r =(2 * small) + 2;
	int i = small;
	if (l < current && arr[l] < arr[small]) { i = l; }
	if (r < current && arr[r] < arr[i]) { i = r; }
	if (i != small) { 
		swap(arr[small], arr[i]); 
		heapify(i); 
	}
}

int Queue::deletemin()
{
	
	int k = arr[0];
	arr[0] = arr[current - 1];
	current--;
	heapify(0);
	return k;
}

bool Queue::getel(int ll)
{
	for (int i = 0; i < current; i++)
	{
		if (i == ll)
		{
			return true;
		}
	}
	return false;
}


int main()
{
	string fff = "";
	ifstream file("d:\\input.txt");
	if (!file.is_open())
	{
		cout << "Nope";
	}
	int k = 0;
	getline(file, fff);
	int kk = fff.size() / 2 + 1;
	while (fff != "Robloh")
	{
		fff = "robloh";
		getline(file, fff);
		k++;
	}
	int** mm = new int* [k];
	for (int i = 0; i < k; i++) mm[i] = new int[kk];
	file.close();
	file.open("d:\\input.txt");

	int ss = 0;
	for (int i = 0; i < k; i++)
	{
		getline(file, fff);
		for (int j = 0; j < kk * 2 - 1; j += 2)
		{
			if (fff[j] == ' ' && fff[j + 1] == ' ') { ss++; mm[i][j/2] = ss; }
			else mm[i][j / 2] = 0;
		}
	}
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < kk; j++)
		{
			cout << "  " << mm[i][j];
		}
		cout << "\n";
	}

	

	int** ms = new int* [ss + 1];
	for (int i = 0; i < ss + 1; i++) ms[i] = new int[ss + 1];

	for (int i = 1; i < ss; i++)
	{
		for (int j = 1; j < ss; j++)
		{
			ms[i][j] = 0;
		}
	}

	//for (int i = 0; i < k; i++)
	//{
	//	for (int j = 0; j < kk; j++)
	//	{
	//		
	//		if (mm[i][j] >= 1)
	//		{
	//			/*ms[21][17] = ms[17][21] = ms[20][19] = ms[19][20] = 1;
	//			ms[20][17] = ms[17][20] = 0;*/
	//			if (i - 1 >= 0) if (mm[i - 1][j] >= 1) { ms[mm[i - 1][j]][mm[i][j]] = 1; ms[mm[i][j]][mm[i - 1][j]] = 1; }
	//			if (j - 1 >= 0) if (mm[i][j - 1] >= 1) { ms[mm[i][j - 1]][mm[i][j]] = 1; ms[mm[i][j]][mm[i][j - 1]] = 1; }
	//			if (i + 1 < k) if (mm[i + 1][j] >= 1) { ms[mm[i + 1][j]][mm[i][j]] = 1; ms[mm[i][j]][mm[i + 1][j]] = 1; }
	//			if (j + 1 < kk) if (mm[i][j + 1] >= 1) { ms[mm[i][j + 1]][mm[i][j]] = 1; ms[mm[i][j]][mm[i][j + 1]] = 1; }
	//			
	//		}
	//	}
	//}

	Adjance(mm, k, kk, ms);
	cout << endl;
	int x, y;
	vector<int>c;
	cout << "Input coordinate: ";	cin >> x;	
	cout << endl;
	cout << "Input end node: ";		cin >> y;	
	//Queue frontier;
	//int node = x;
	//bool* used = new bool[ss];
	//for (int i = 1; i < ss; i++) { used[i] = false; }
	//frontier.push(x);
	//while (!frontier.empty())
	//{
	//	if (frontier.empty())
	//	{
	//		break;
	//	}
	//	node = frontier.deletemin();
	//	if (node == y)
	//	{
	//		cout << "END";
	//		break;
	//	}
	//	used[node] = true;
	//	for (int i = 1; i < ss; i++)
	//	{
	//		int v = ms[node][i];
	//		if (v == 1 && !used[i])
	//		{
	//			frontier.push(i);
	//			c.push_back(i);
	//		}
	//	}
	//	cout << frontier.getmin() << " ";
	//}
	////
	//for (int i = 0; i < c.size(); i++)
	//{
	//	cout << c[i] << " ";
	//}

	/*Queue openset;
	Queue closedset;
	int* g = new int[ss];
	for (int i = 1; i < ss; i++) { g[i] = INT_MAX; }
	g[x] = 0;
	int* f = new int[ss];
	for (int i = 1; i < ss; i++) { f[i] = 0; }
	openset.push(x);
	f[x] = g[x] + h(x, y,mm,k,kk);
	while (!openset.empty())
	{
		int current = openset.getmin();
			if (current == y)
			{
				cout << "END" << endl;
				c.push_back(y);
				break;
			}
		closedset.push(current);
		c.push_back(current);
		openset.deletemin();
		for (int i = 1; i < ss; i++)
		{
			int v = ms[current][i];
			if (v)
			{
				int tempg = g[i] + 1;
				if (tempg<g[i])
				{
					g[i] = tempg;
					f[i] = g[i] + h(i, y, mm, k, kk);
					if (!openset.getel(i))
					{
						openset.push(i);
					}
					
				}
			}
		}
	}*/
	A_star(ss, ms, c, x, y, mm, k, kk);
	cout << endl;
	file_out(c, mm, k, kk);
	/*for (int i = 0; i < c.size(); i++)
	{
		cout << c[i] << " ";
	}
	ofstream fout;
	fout.open("d:\\output.txt");
	bool is;
	for (int i = 0; i < k; i++)
	{
		cout << "\n | ";
		for (int j = 0; j < kk; j++)
		{
			is = false;
			for (int o = 0; o < c.size(); o++)
			{
				if (mm[i][j] == c[o])
				{
					is = true;
					
					cout << symb(o) << ' '; fout << symb(o) << ' ';
					break;
				}
			}
				if (is == false)
				{
					if (mm[i][j] == 0) { cout << "X ";	fout << "X "; }
					else { cout << "  ";	fout << " "; }
				}
			
		}
		fout << endl;
		cout << "|";
	}*/
	return 0;
}

void Adjance(int** mm, int k, int kk, int** ms)
{
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < kk; j++)
		{

			if (mm[i][j] >= 1)
			{
				/*ms[21][17] = ms[17][21] = ms[20][19] = ms[19][20] = 1;
				ms[20][17] = ms[17][20] = 0;*/
				if (i - 1 >= 0) if (mm[i - 1][j] >= 1) { ms[mm[i - 1][j]][mm[i][j]] = 1; ms[mm[i][j]][mm[i - 1][j]] = 1; }
				if (j - 1 >= 0) if (mm[i][j - 1] >= 1) { ms[mm[i][j - 1]][mm[i][j]] = 1; ms[mm[i][j]][mm[i][j - 1]] = 1; }
				if (i + 1 < k) if (mm[i + 1][j] >= 1) { ms[mm[i + 1][j]][mm[i][j]] = 1; ms[mm[i][j]][mm[i + 1][j]] = 1; }
				if (j + 1 < kk) if (mm[i][j + 1] >= 1) { ms[mm[i][j + 1]][mm[i][j]] = 1; ms[mm[i][j]][mm[i][j + 1]] = 1; }

			}
		}
	}
}

char symb(int N)
{
	while (N > 60)
	{
		N -= 60;
	}
	if (N == 0) return '!';//start
	else if (N < 10) return N + 48;
	else if (N + 87 <= 122) return N + 87;
	else if (N + 29 <= 87) return N + 29; //для - 'X'
	else if (N + 30 <= 90) return N + 30;
	return '+';
}
int h(int x,int y,int**ms,int k,int kk)
{
	int x1 = 0, x2 = 0, y1 = 0, y2 = 0;

	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < kk; j++)
		{
			if (ms[i][j] == x) { x1 = i;	y1 = j; }
			if (ms[i][j] == y) {
				x2 = i; y2 = j;
			}

		}
	}
		int dx = abs(x1 - x2);
		int dy = abs(y1 - y2);
		return dx + dy;
	
}

void A_star(int ss, int** ms, vector<int>& c,int x,int y,int**mm,int k,int kk)
{
	Queue openset;
	bool* used = new bool[ss+1];
	for (int i = 1; i < ss; i++) { used[i] = false; }

	int* g = new int[ss+1];
	for (int i = 1; i < ss; i++) { g[i] = INT_MAX; }
	g[x] = 0;
	int* f = new int[ss+1];
	for (int i = 1; i < ss; i++) { f[i] = 0; }
	openset.push(x);
	f[x] = g[x] + h(x, y, mm, k, kk);
	while (!openset.empty())
	{
		int current = openset.getmin();
		if (current == y)
		{
			cout << "END" << endl;
			c.push_back(y);
			break;
		}
		used[current]=true;
		c.push_back(current);
		openset.deletemin();
		for (int i = 1; i < ss; i++)
		{
			int v = ms[current][i];
			if (v)
			{
				int tempg = g[i] + 1;
				if (tempg < g[i])
				{
					g[i] = tempg;
					f[i] = g[i] + h(i, y, mm, k, kk);
					if (!openset.getel(i))
					{
						openset.push(i);
					}

				}
			}
		}
	}
}

void file_out(vector<int>& c, int** mm, int k, int kk)
{
	ofstream fout;
	fout.open("d:\\output.txt");
	bool is;
	for (int i = 0; i < k; i++)
	{
		cout << "\n | ";
		for (int j = 0; j < kk; j++)
		{
			is = false;
			for (int o = 0; o < c.size(); o++)
			{
				if (mm[i][j] == c[o])
				{
					is = true;

					cout << symb(o) << ' '; fout << symb(o) << ' ';
					break;
				}
			}
			if (is == false)
			{
				if (mm[i][j] == 0) { cout << "X ";	fout << "X "; }
				else { cout << "  ";	fout << " "; }
			}

		}
		fout << endl;
		cout << "|";
	}
}