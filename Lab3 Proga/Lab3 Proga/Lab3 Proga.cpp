#include<fstream>
#include <iostream>
#include<string>
#include<utility>
#include<algorithm>
#include<vector>
#include<cmath>
#include<iomanip>
#include<queue>
char symb(int N);
using namespace std;
int curr;
void swap(int& t, int& k) { int temp = t; t = k; k = temp; }
int h(int x, int y, int** ms, int k, int kk);
void Adjance(int** mm, int k, int kk, int** ms);
void A_star(int ss, int** ms, int x, int y, int** mm, int k, int kk, int* prev);
void reconstructpath(vector<int>& c, int* prev, int x, int y);
void file_out(vector<int>& c, int** mm, int k, int kk);


class Queue
{
	int* Va; int* Po;	//to store elements
	int current;
public:
	Queue(int size)
	{
		Po = new int[size];
		Va = new int[size];
		current = 0;
	}
	void push(int value, int pos)
	{
		Va[current] = value;
		Po[current] = pos;
		current++;
		for (int i = 0; i < current; i++)
		{
			for (int j = i + 1; j < current; j++)
			{
				if (Po[i] > Po[j])
				{
					int temp = Po[i];
					Po[i] = Po[j];
					Po[j] = temp;
					
					int tmp = Va[i];
					Va[i] = Va[j];
					Va[j] = tmp;
				}
			}
		}
	}
	bool empty()
	{
		return current == 0;
	}
	void pop()
	{
		for (int i = 0; i < current - 1; i++)
		{
			Va[i] = Va[i + 1];
		}
		current--;
	}
	int getmin()
	{
		return Va[0];
	}
};


int main()
{
	string fff = "";
	ifstream file("d:\\Y.txt");
	if (!file.is_open())
	{
		cout << "Nope";
	}
	int k = 0;
	getline(file, fff);
	int kk = fff.size() / 2 + 1;
	while (fff != "maxloh")
	{
		fff = "maxloh";
		getline(file, fff);
		k++;
	}
	int** mm = new int* [k];
	for (int i = 0; i < k; i++) mm[i] = new int[kk];
	file.close();
	file.open("d:\\Y.txt");
	vector<vector<int>>Lab;
	vector<int>La;
	int ss = 0;
	for (int i = 0; i < k; i++)
	{
		getline(file, fff);
		for (int j = 0; j < kk * 2 - 1; j += 2)
		{
			if (fff[j] == ' ' && fff[j + 1] == ' ')
			{
				ss++;
				mm[i][j / 2] = ss;
				
			}
			else mm[i][j / 2] = 0;
		}
	}
	
	cout << "Labyrinth nodes: " << endl;
	

	cout << endl << endl;
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < kk; j++)
		{
			cout << setw(6) << mm[i][j] << setw(6);
		}
		cout << "\n" << " ";
	}
	
	

	int** ms = new int* [ss];
	for (int i = 1; i <= ss; i++) ms[i] = new int[ss];

	for (int i = 1; i <= ss; i++)
	{
		for (int j = 1; j <= ss; j++)
		{
			ms[i][j] = 0;
		}
	}
	Adjance(mm, k, kk, ms);
	cout << endl;
	int x, y;
	vector<int>c;
	cout << "Input coordinate: ";	cin >> x;
	cout << endl;
	cout << "Input end node: ";		cin >> y;
	
	for (int i = 0; i < La.size(); i++)
	{
		cout << La[i] << " ";
	}
	int* prev = new int[ss];
	for (int i = 0; i < ss; i++) { prev[i] = 0; }
	A_star(ss, ms, x, y, mm, k, kk, prev);
	reconstructpath(c, prev, x, y);
	cout << endl;
	file_out(c, mm, k, kk);


	return 0;
}

void Adjance(int** mm, int k, int kk, int** ms)
{
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < kk; j++)
		{
			if (mm[i][j] >= 1 && mm[i][j + 1] >= 1)
			{
				ms[mm[i][j]][mm[i][j + 1]] = 1;
				ms[mm[i][j + 1]][mm[i][j]] = 1;
			}
			if (mm[i][j] >= 1 && mm[i + 1][j] >= 1)
			{
				ms[mm[i][j]][mm[i + 1][j]] = 1;
				ms[mm[i + 1][j]][mm[i][j]] = 1;
			}
			//For diagonal movement
			/*if (mm[i][j]>=1 &&mm[i+1][j+1]>=1)
			{
				ms[mm[i][j]][mm[i + 1][j + 1]] = 1;
				ms[mm[i+1][j+1]][mm[i][j]] = 1;

			}
			if (mm[i][j] >= 1 && mm[i - 1][j - 1] >= 1)
			{
				ms[mm[i][j]][mm[i - 1][j - 1]] = 1;
				ms[mm[i - 1][j - 1]][mm[i][j]] = 1;
			}
			if (mm[i][j] >= 1 && mm[i + 1][j - 1] >= 1)
			{
				ms[mm[i][j]][mm[i + 1][j - 1]] = 1;
				ms[mm[i + 1][j - 1]][mm[i][j]] = 1;
			}*/
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
int h(int x, int y, int** ms, int k, int kk)
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
	return 4 * (dx + dy) + (4 - 2 * 8) * min(dx, dy);
	//return sqrt(dx * dx + dy * dy);
	//return(dx * dx + dy * dy);
	//return (dx + dy);

}

void A_star(int ss, int** ms, int x, int y, int** mm, int k, int kk, int* prev)
{
	
	Queue S(ss);
	bool* used = new bool[ss];
	for (int i = 1; i <= ss; i++) { used[i] = false; }
	int* g = new int[ss];
	for (int i =1; i <= ss; i++) { g[i] = INT_MAX; }
	g[x] = 0;
	prev[x] = 0;
	int* f = new int[ss];
	for (int i = 1; i <= ss; i++) { f[i] = 0; }
	f[x] = g[x] + h(x, y, mm, k, kk);
	S.push(x, f[x]);
	while (!S.empty())
	{
		
		int current = S.getmin();
		if (current == y)
		{
			cout << "END" << endl;

			break;
		}
		used[current] = true;
		S.pop();
		for (int i = 1; i <=ss; i++)
		{
			int v = ms[current][i];

			if (v >0)
			{

				if (g[current] + 1 < g[i])
				{
					prev[i] = current;
					g[i] = g[current] + 1;
					f[i] = g[i] + h(i, y, mm, k, kk);
					if (!used[i])
					{
						S.push(i, f[i]);
					}

				}
			}
		}
	}
}

void reconstructpath(vector<int>& c, int* prev, int x, int y)
{
	curr = y;
	c.push_back(curr);
	while (curr != x &&curr>0)
	{
		curr = prev[curr];
		c.push_back(curr);
	}
	
	c.push_back(x);
	reverse(c.begin(), c.end());
}


void file_out(vector<int>& c, int** mm, int k, int kk)
{
	ofstream fout;
	fout.open("d:\\output.txt");
	bool is;
	if (curr == 0) { cout << "No Path"; }
	else
	{
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
}

