#include <fstream>
#include <iostream>
#include <string>
#include<algorithm>
#include <vector>

using namespace std;

struct Vertex
{
	int i, j;
	int ksos = 0;// кількість sosedi'в
	int sosedi[8] = { -1 };
};

void sol(Vertex* mVert, int** mm, int k, int kk);
char symb(int N);
void lout(int** mm, int k, int kk);
int reconstructpath(int* prev, vector<int>& c, int x, int y);
int h(int x, int y, int** mm, int k, int kk);
void file_out(vector<int>& c, int** mm, int k, int kk);
void A_star(Vertex* node, int k, int kk, int** mm, int* prev, int ss, int x, int y);


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
	int ss = 0;
	for (int i = 0; i < k; i++)
	{
		getline(file, fff);
		for (int j = 0; j < kk * 2 - 1; j += 2)
		{
			if (fff[j] == ' ' && fff[j + 1] == ' ') { ss++; mm[i][j / 2] = ss; }
			else mm[i][j / 2] = 0;
		}
	}
	Vertex* mVert = new Vertex[ss];
	lout(mm, k, kk);
	int Sv, Ev;
	cout << "\n Start vertex: ";
	cin >> Sv;
	if (Sv > ss || Sv < 1) { cout << " [!] Wrong vertex"; return -1; }
	cout << "\n Finish vertex: ";
	cin >> Ev;
	if (Ev > ss || Ev < 1) { cout << " [!] Wrong vertex"; return -1; }
	///
	sol(mVert, mm, k, kk);
	///
	int* prev = new int[ss];
	for (int i = 0; i < ss; i++) prev[i] = 0;
	vector<int>c;
	A_star(mVert, k, kk, mm, prev, ss, Sv, Ev);
	int current=reconstructpath(prev, c, Sv, Ev);
	if (current == 0) { cout << "No Path: "; }
	else{ file_out(c, mm, k, kk); }
	///
}

int reconstructpath(int* prev, vector<int>& c, int x, int y)
{
	int curr = y;

	c.push_back(curr);
	while (curr != x && curr > 0)
	{
		curr = prev[curr];
		c.push_back(curr);
	}
	c.push_back(x);
	reverse(c.begin(), c.end());
	return curr;
}
int h(int x, int y, int** mm, int k, int kk)
{
	int x1, x2, y1, y2;
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < kk; j++)
		{
			if (mm[i][j] == x)
			{
				x1 = i; x2 = j;
			}
			if (mm[i][j] == y)
			{
				y1 = i; y2 = j;
			}
		}
	}
	int dx = abs(x1 - y1);
	int dy = abs(x2 - y2);
	return 4 * (dx + dy) + (4 - 2 * 8) * min(dx, dy);
	//return sqrt(dx * dx + dy * dy);
	//return(dx * dx + dy * dy);
	//return (dx + dy);
}
void A_star(Vertex* node, int k, int kk, int** mm, int* prev, int ss, int x, int y)
{
	Queue Q(ss);
	int* g = new int[ss];
	bool* used = new bool[ss];
	int* f = new int[ss];
	for (int i = 0; i < ss; i++) { g[i] = INT_MAX; f[i] = 0; used[i] = false; }
	g[y] = INT_MAX;
	g[x] = 0;
	f[x] = g[x] + h(x, y, mm, k, kk);
	Q.push(x, f[x]);
	while (!Q.empty())
	{
		int current = Q.getmin();
		used[current] = true;
		if (current == y) { break; }////
		Q.pop();
		for (int i = 0; i < node[current - 1].ksos; i++)
		{	
			if (g[node[current - 1].sosedi[i]] > g[current] + 1)
			//With diagonal movement only
			//if (g[node[current - 1].sosedi[i]] > g[current] + (node[current - 1].i == node[node[current - 1].sosedi[i] - 1].i || node[current - 1].j == node[node[current - 1].sosedi[i] - 1].j ? 10000000 : 14142135))
			{
				//cout << (node[current - 1].i == node[node[current - 1].sosedi[i] - 1].i || node[current - 1].j == node[node[current - 1].sosedi[i] - 1].j ? 10000000 : 14142135) << " " << node[current-1].i << " " << node[current-1].j << " " << node[node[current-1].sosedi[i]-1].i << " " << node[node[current-1].sosedi[i]-1].j << "\n";
				//g[node[current - 1].sosedi[i]] = g[current] + (node[current - 1].i == node[node[current - 1].sosedi[i] - 1].i || node[current - 1].j == node[node[current - 1].sosedi[i] - 1].j ? 10000000 : 14142135);
				g[node[current - 1].sosedi[i]] = g[current] + 1;
				prev[node[current - 1].sosedi[i]] = current;
				f[node[current - 1].sosedi[i]] = g[node[current - 1].sosedi[i]] + h(node[current - 1].sosedi[i], y, mm, k, kk);
				if (!used[node[current - 1].sosedi[i]])
				{
					Q.push(node[current - 1].sosedi[i], f[node[current - 1].sosedi[i]]);
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
				for (unsigned int o = 0; o < c.size(); o++)
				{
					if (mm[i][j] == c[o])
					{
						is = true;

						cout << symb(o - 1) << ' '; fout << symb(o - 1) << ' ';
						break;
					}
				}
				if (is == false)
				{
					if (mm[i][j] == 0) { cout << "X ";	fout << "X "; }
					else { cout << "  ";	fout << "  "; }
				}
			}
			fout << endl;
			cout << "|";
		}
	
}
void sol(Vertex* mVert, int** mm, int k, int kk)
{
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < kk; j++)
		{
			if (mm[i][j] >= 1)
			{
				mVert[mm[i][j] - 1].i = i;
				mVert[mm[i][j] - 1].j = j;
				//For diagonal movement
				if (i + 1 < k && j + 1 < kk)
				{
					if (mm[i + 1][j + 1] >= 1)
					{
						mVert[mm[i][j] - 1].sosedi[mVert[mm[i][j] - 1].ksos] = mm[i + 1][j + 1];
						mVert[mm[i + 1][j + 1] - 1].sosedi[mVert[mm[i + 1][j + 1] - 1].ksos] = mm[i][j];
						mVert[mm[i + 1][j + 1] - 1].ksos++; mVert[mm[i][j] - 1].ksos++;
					}
				}
				if (i + 1 < k && j - 1 >= 0)
				{
					if (mm[i + 1][j - 1] >= 1)
					{
						mVert[mm[i][j] - 1].sosedi[mVert[mm[i][j] - 1].ksos] = mm[i + 1][j - 1];
						mVert[mm[i + 1][j - 1] - 1].sosedi[mVert[mm[i + 1][j - 1] - 1].ksos] = mm[i][j];
						mVert[mm[i + 1][j - 1] - 1].ksos++; mVert[mm[i][j] - 1].ksos++;
					}
				}
				//
				if (i + 1 < k)
				{
					if (mm[i + 1][j] >= 1)
					{
						mVert[mm[i][j] - 1].sosedi[mVert[mm[i][j] - 1].ksos] = mm[i + 1][j];
						mVert[mm[i + 1][j] - 1].sosedi[mVert[mm[i + 1][j] - 1].ksos] = mm[i][j];
						mVert[mm[i + 1][j] - 1].ksos++; mVert[mm[i][j] - 1].ksos++;
					}
				}
				if (j + 1 < kk)
				{
					if (mm[i][j + 1] >= 1)
					{
						mVert[mm[i][j] - 1].sosedi[mVert[mm[i][j] - 1].ksos] = mm[i][j + 1];
						mVert[mm[i][j + 1] - 1].sosedi[mVert[mm[i][j + 1] - 1].ksos] = mm[i][j];
						mVert[mm[i][j + 1] - 1].ksos++; mVert[mm[i][j] - 1].ksos++;
					}
				}
			}
		}
	}
}
void lout(int** mm, int k, int kk) // вивід оцифрованого лабіринту з номерами вершин
{
	cout << " -\n";
	for (int i = 0; i < k; i++)
	{
		cout << " ";
		for (int j = 0; j < kk; j++) cout << mm[i][j] << " \t";
		cout << "\n";
	}
	cout << " -\n";
}
char symb(int N)
{
	while (N > 60)
	{
		N -= 60;
	}
	if (N == -1) return '!';//0 //start
	else if (N < 10) return N + 48;
	else if (N + 87 <= 122) return N + 87;
	else if (N + 29 <= 87) return N + 29; //для - 'X'
	else if (N + 30 <= 90) return N + 30;
	return '+';
}