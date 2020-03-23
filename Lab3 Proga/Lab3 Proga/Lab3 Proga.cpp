#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void sss(int** mm, int ss, int V, int* bb, int& nn, int* ll);
void delbtw(int* ll, int& nn, int ii, int jj, int** ms);
void df(int* ll, int& s, int kn);
void outr(int** mm, int* ll, int k, int kk, int nn);
void shrink(int** ms, int* ll, int& nn, int Vl);
void sumig(int** ms, int** mm, int ss, int k, int kk);
void way(int** mm, int* ll, int nn, int k, int kk);
char symb(int N);

int main()
{
	string fff = "";
	ifstream file("input.txt");
	int k = 0;
	getline(file, fff);
	int kk = fff.size() / 2 + 1;
	while (fff != "maxloh-V2")//xD
	{
		fff = "maxloh-V2";//xD
		getline(file, fff);
		k++;
	}
	int** mm = new int* [k];
	for (int i = 0; i < k; i++) mm[i] = new int[kk];
	file.close();
	file.open("input.txt");

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
	file.close();

	cout << " Our Labyrinth and Vertices:\n";
	for (int i = 0; i < k; i++)
	{
		if (i == 0) { for (int jj = 0; jj < kk; jj++) cout << "\t---"; cout << "\n"; }
		for (int j = 0; j < kk; j++)
		{
			if(mm[i][j]==0) cout << "\t | ";
			else cout << "\t(" << mm[i][j] << ")";
		}
		cout << "\n";
		if (i == k - 1) for (int jj = 0; jj < kk; jj++) cout << "\t---";
	}

	int** ms = new int* [ss];
	for (int i = 0; i < ss; i++) ms[i] = new int[ss];

	sumig(ms, mm, ss, k, kk);
	int V;
	cout << "\n Print *Start* vertex: ";
	cin >> V;
	if (V > ss || V <=0) { cout << " [!] Wrong vertex number [!]"; return 1; }
	V--;

	int Vl;
	cout << " Print *Finish* vertex: ";
	cin >> Vl;
	if (Vl > ss || Vl <= 0) { cout << " [!] Wrong vertex number [!]"; return 1; }
	Vl--;

	int* bb = new int[ss];
	for (int i = 0; i < ss; i++) bb[i] = 0;

	int* ll = new int[ss*ss];
	int nn = 0;

	sss(ms, ss, V, bb, nn, ll);

	shrink(ms, ll, nn, Vl);
	if (ll[0] != Vl) { cout << "\n No way..................................... [!!!]"; return 1;  }
	outr(mm, ll, k, kk, nn);
	return 0;
}

void sumig(int** ms, int** mm, int ss, int k, int kk)
{
	for (int i = 0; i < ss; i++)
	{
		for (int j = 0; j < ss; j++)
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
				if (i - 1 >= 0) if (mm[i - 1][j] >= 1) { ms[mm[i - 1][j] - 1][mm[i][j] - 1] = 1; ms[mm[i][j] - 1][mm[i - 1][j] - 1] = 1; }
				if (j - 1 >= 0) if (mm[i][j - 1] >= 1) { ms[mm[i][j - 1] - 1][mm[i][j] - 1] = 1; ms[mm[i][j] - 1][mm[i][j - 1] - 1] = 1; }
				if (i + 1 < k)  if (mm[i + 1][j] >= 1) { ms[mm[i + 1][j] - 1][mm[i][j] - 1] = 1; ms[mm[i][j] - 1][mm[i + 1][j] - 1] = 1; }
				if (j + 1 < kk) if (mm[i][j + 1] >= 1) { ms[mm[i][j + 1] - 1][mm[i][j] - 1] = 1; ms[mm[i][j] - 1][mm[i][j + 1] - 1] = 1; }
			}
		}
	}
	//for (int i = 0; i < ss; i++)
	//{
	//	cout << "\n\t";
	//	for (int j = 0; j < ss; j++) cout << ms[i][j] << "";
	//}
}
void shrink(int** ms, int* ll, int& nn, int Vl)
{
	cout << " ----\n | 1 - Result " << nn << ": ";
	for (int i = nn - 1; i >= 0; i--) cout << "(" << ll[i] + 1 << ")";

	for (int i = 0; i < nn; i++) if (ll[i] == Vl) { df(ll, nn, i); break; }

	cout << "\n ----\n | 2 - Result " << nn << ": ";
	for (int i = nn - 1; i >= 0; i--) cout << "(" << ll[i] + 1 << ")";

	for (int ii = 0; ii < nn; ii++)
	{
		for (int i = 0; i < nn - 2; i++)//
		{
			for (int j = i+2; j < nn; j++)
			{
				if (ms[ll[j]][ll[i]] == 1)
				{
					delbtw(ll, nn, i + 1, j, ms);
				}
			}
		}
	}
	cout << "\n ----\n | 3 - Result " << nn << ": ";
	for (int i = nn - 1; i >= 0; i--) cout << "(" << ll[i] + 1 << ")";
	cout << "\n ----\n";
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
void way(int **mm, int *ll, int nn, int k, int kk)
{
	ofstream fout;
	fout.open("output.txt");
	bool is = false;
	for (int i = 0; i < k; i++)
	{
		cout << "\n | ";
		for (int j = 0; j < kk; j++)
		{
			//Переробить мб
			is = false;
			for (int jk = nn - 1; jk >= 0; jk--) if (mm[i][j] == ll[jk] + 1) { is = true; cout << symb(nn - jk - 1) << ' '; fout << symb(nn - jk - 1) << ' '; break; }
			if (is == false)
			{
				if (mm[i][j] == 0) { cout << "X "; fout << "X "; }
				else { cout << "  "; fout << "  "; }
			}
		}
		fout << endl;
		cout << "|";
	}
	fout.close();
}
void outr(int** mm, int* ll, int k, int kk, int nn)
{
	cout << "\n -";
	for (int i = 0; i < kk + 1; i++)
	{
		cout << "--";
	}
	way(mm, ll, nn, k, kk);
	cout << "\n -";
	for (int i = 0; i < kk + 1; i++)
	{
		cout << "--";
	}
}
void df(int* ll, int& s, int kn)
{
	for (int i = 0; i < s-kn; i++)
	{
		ll[i] = ll[i+kn];
	}
	s -= kn;
}
void delbtw(int* ll, int& nn, int ii, int jj, int** ms)
{
	for (int i = ii; i < nn - (jj - ii); i++)
	{
		ll[i] = ll[i + (jj - ii)];
	}
	nn -= (jj - ii);
}
void sss(int** ms, int ss, int V, int* bb, int& nn, int* ll)
{
	bb[V] = 1;
	for (int i = 0; i < ss; i++)
	{
		if (ms[V][i] == 1 && bb[i] == 0)
		{
			sss(ms, ss, i, bb, nn, ll);
		}
	}
	bb[nn] = 0;
	ll[nn] = V;
	nn++;
}