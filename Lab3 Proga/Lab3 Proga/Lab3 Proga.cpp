#include<fstream>
#include <iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<iomanip>
struct Vertex
{
	int i, j;
	int ksos = 0;// кількість sosedi'в
	int sosedi[8] = { -1 };
};
char symb(int N);
using namespace std;
int curr;
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
	//return 4 * (dx + dy) + (4 - 2 * 8) * min(dx, dy);
	//return sqrt(dx * dx + dy * dy);
	//return(dx * dx + dy * dy);
	return (dx + dy);
}
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

void lout(int** mm, int k, int kk);

void A_star(Vertex* node, int k, int kk, int** mm, int* prev, int ss, int x, int y)
{
	Queue Q(ss);
	int* g = new int[ss];
	bool* used = new bool[ss];
	int* f = new int[ss];
	for (int i = 0; i < ss; i++) { g[i] = INT_MAX; f[i] = 0; used[i] = false; }
	g[y]=INT_MAX;
	g[x] = 0;
	f[x] = g[x] + h(x, y, mm, k, kk);
	Q.push(x, f[x]);
	while (!Q.empty())
	{
		int current = Q.getmin();
		used[current] = true;
	
		if (current == y)
		{
			cout << "END: ";
			break;
		}
		Q.pop();
		for (int i = 0; i < node[current - 1].ksos; i++)
		{
			if (g[node[current-1].sosedi[i]] > g[current] + 1)
			{
				g[node[current-1].sosedi[i]] = g[current] + 1;
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
void reconstructpath(int* prev, vector<int>& c, int x, int y)
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
					else { cout << "  ";	fout << "  "; }
				}

			}
			fout << endl;
			cout << "|";
		}
	}
}

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
	int Sv, Ev, Ei, Ej;
	cout << "\n Start vertex: ";
	cin >> Sv;
	cout << "\n Finish vertex: ";
	cin >> Ev;
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < kk; j++)
		{
			if (mm[i][j] >= 1)
			{
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
	int* prev = new int[ss];
	for (int i = 0; i < ss; i++)
	{
		prev[i] = 0;
	}
	vector<int>c;
	A_star(mVert, k, kk, mm, prev, ss, Sv, Ev);
	reconstructpath(prev, c, Sv, Ev);
	file_out(c, mm, k, kk);
}

void lout(int** mm, int k, int kk) // вивід оцифрованого лабіринту з номерами вершин
{
	cout << " -\n";
	for (int i = 0; i < k; i++)
	{
		cout << " ";
		for (int j = 0; j < kk; j++) cout << mm[i][j] << "\t";
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
	if (N == 0) return '!';//start
	else if (N < 10) return N + 48;
	else if (N + 87 <= 122) return N + 87;
	else if (N + 29 <= 87) return N + 29; //для - 'X'
	else if (N + 30 <= 90) return N + 30;
	return '+';
}


