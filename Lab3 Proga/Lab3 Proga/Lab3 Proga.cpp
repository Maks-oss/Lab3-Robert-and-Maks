#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void sss(int** mm, int ss, int V, bool* bb, int& nn, int* ll);
void delbtw(int* ll, int& nn, int ii, int jj);
void cccc(int kkk);
void df(int* ll, int& s, int kn);

int main()
{
	string fff = "";
	ifstream file("input.txt");
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
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < kk; j++)
		{
			if(mm[i][j]==0) cout << " \t---";
			else cout << " \t(" << mm[i][j] << ")";
		}
		cout << "\n";
	}

	int** ms = new int* [ss];
	for (int i = 0; i < ss; i++) ms[i] = new int[ss];

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

	for (int i = 0; i < ss; i++)
	{
		cout << "\n\t";
		for (int j = 0; j < ss; j++)
		{
			cout << ms[i][j] << "";
		}
	}

	int V;
	cout << "\n\n Print Start: ";
	cin >> V;
	if (V > ss || V <=0) { cout << " [!] Wrong number [!]"; return 1; }
	V--;

	int Vl;
	cout << " Print Finish: ";
	cin >> Vl;
	if (Vl > ss || Vl <= 0) { cout << " [!] Wrong number [!]"; return 1; }
	Vl--;

	bool* bb = new bool[ss];
	for (int i = 0; i < ss; i++) bb[i] = false;

	int* ll = new int[ss];
	int nn = 0;

	sss(ms, ss, V, bb, nn, ll);

	cout << " ------------------------------------------------------\n | 1 - Result " << nn << ": ";
	for (int i = nn - 1; i >= 0; i--) cout << "(" << ll[i] + 1 << ")";

	for (int i = nn - 1; i >= 0; i--) if (ll[i] == Vl) { df(ll, nn, i); break; }

	cout << "\n ------------------------------------------------------\n | 2 - Result " << nn << ": ";
	for (int i = nn - 1; i >= 0; i--) cout << "(" << ll[i] + 1 << ")";

	for (int i = 0; i < nn - 2; i++)
	{
		for (int j = i + 2; j < nn; j++)
		{
			if (ms[ll[j]][ll[i]] == 1)
			{
				delbtw(ll, nn, i + 1, j);
			}
		}
	}

	cout << "\n ------------------------------------------------------\n | 3 - Result " << nn << ": ";
	for (int i = nn - 1; i >= 0; i--) cout << "(" << ll[i] + 1 << ")";
	cout << "\n ------------------------------------------------------";

	if (ll[0] != Vl) { cout << "\n No way..................................... [!!!]"; return 1;  }

	bool is = false;
	cout << "\n -";
	for (int i = 0; i < k+1; i++)
	{
		cout << "--";
	}
	for (int i = 0; i < k; i++)
	{
		cout << "\n | ";
		for (int j = 0; j < kk; j++)
		{
			//Переробить мб
			is = false;
			for (int jk = nn - 1; jk >= 0; jk--) if (mm[i][j] == ll[jk] + 1) { is = true; cccc(nn - jk - 1); break; }
			if (is == false)
			{
				if (mm[i][j] == 0) cout << "X ";
				else cout << "  ";
			}
		}
		cout << "|";
	}
	cout << "\n -";
	for (int i = 0; i < k + 1; i++)
	{
		cout << "--";
	}
	return 0;
}

void df(int* ll, int& s, int kn)
{
	for (int i = 0; i < s-kn; i++)
	{
		ll[i] = ll[i+kn];
	}
	s -= kn;
}
void cccc(int kkk)
{
	if (kkk == 0) cout << "S ";
	else cout << std::hex << kkk << " ";
	/*
	switch (kkk)
	{
	case 0: cout << "S "; break;
	case 10: cout << "a "; break;
	case 11: cout << "b "; break;
	case 12: cout << "c "; break;
	case 13: cout << "d "; break;
	case 14: cout << "e "; break;
	case 15: cout << "f "; break;
	default: cout << kkk << " ";
	}
	*/
}
void delbtw(int* ll, int& nn, int ii, int jj)
{
	for (int i = ii; i < nn - (jj - ii); i++)
	{
		//cout << i << " " << ll[i] + 1 << "\n";
		ll[i] = ll[i + (jj - ii)];
	}
	//cout << jj - ii << "\n";
	nn -= (jj - ii);
}
void sss(int** ms, int ss, int V, bool* bb, int& nn, int* ll)
{
	bb[V] = 1;
	for (int i = 0; i < ss; i++)
	{
		if (ms[V][i] == 1 && bb[i] == 0)
		{
			sss(ms, ss, i, bb, nn, ll);
		}
	}
	ll[nn] = V;
	nn++;
}