#include<fstream>
#include <iostream>
#include<string>

using namespace std;

void sss(int** mm, int ss, int V, bool* bb, int& nn, int* ll);
void delbtw(int* ll, int& nn, int ii, int jj);
void cccc(int kkk);

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
				if (i - 1 >= 0) if (mm[i - 1][j] >= 1) { ms[mm[i - 1][j]-1][mm[i][j] - 1]=1; ms[mm[i][j] - 1][mm[i - 1][j] - 1]=1; }
				if (j - 1 >= 0) if (mm[i][j - 1] >= 1) { ms[mm[i][j-1] - 1][mm[i][j] - 1]=1; ms[mm[i][j] - 1][mm[i][j-1] - 1]=1; }
				if (i + 1 < k)  if (mm[i + 1][j] >= 1) { ms[mm[i+1][j] - 1][mm[i][j] - 1]=1; ms[mm[i][j] - 1][mm[i + 1][j] - 1]=1; }
				if (j + 1 < kk) if (mm[i][j + 1] >= 1) { ms[mm[i][j+1] - 1][mm[i][j] - 1]=1; ms[mm[i][j] - 1][mm[i][j+1] - 1]=1; }
			}
		}
	}

	for (int i = 0; i < ss; i++)
	{
		cout << "\n";
		for (int j = 0; j < ss; j++)
		{
			cout << ms[i][j] << " ";
		}
	}

	int V;
	cout << "\n\n Print First: ";
	cin >> V;
	V--;

	bool* bb = new bool[ss];
	for (int i = 0; i < ss; i++) bb[i] = false;

	int* ll = new int[ss];
	int nn = 0;
	/*
	for (int i = 0; i < ss; i++)
	{
		if (bb[i] == false) sss(ms, ss, i, bb, nn, ll);
	}
	*/
	sss(ms, ss, V, bb, nn, ll);

	cout << " ---\n Result " << nn << ": ";
	for (int i = nn - 1; i >= 0; i--) cout << "(" << ll[i]+1 << ")";
	cout << "\n ---";

	for (int i = 0 ; i < nn-2; i++)
	{
		for (int j = i+2; j < nn; j++)
		{
			if (ms[ll[j]][ll[i]] == 1)
			{
				delbtw(ll, nn, i + 1, j);
			}
		}
	}
	bool is = false;

	for (int i = 0; i < k; i++)
	{
		cout << "\n";
		for (int j = 0; j < kk; j++)
		{
			//Переробить
			is = false;
			for (int jk = nn - 1; jk >= 0; jk--) if (mm[i][j] == ll[jk] + 1) { is = true; cccc(nn-jk-1); break; }
			if (is == false)
			{
				if (mm[i][j] == 0) cout << "X ";
				else cout << "  ";
			}
		}
	}

	cout << "\n ---\n Result " << nn << ": ";
	for (int i = nn - 1; i >= 0; i--) cout << "(" << ll[i]+1 << ")";
	cout << "\n ---";
	return 0;
}

void cccc(int kkk)
{
	/// Переробить
	switch (kkk)
	{
	case 0: cout << "  "; break; 
	case 10: cout << "a "; break;
	case 11: cout << "b "; break;
	case 12: cout << "c "; break;
	case 13: cout << "d "; break;
	case 14: cout << "e "; break;
	case 15: cout << "f "; break;
	default: cout << kkk << " ";
	}
}
void delbtw(int* ll, int &nn, int ii, int jj)
{
	for (int i = ii; i < nn - (jj - ii); i++)
	{
		//cout << i << " " << ll[i] + 1 << "\n";
		ll[i] = ll[i+(jj-ii)];
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