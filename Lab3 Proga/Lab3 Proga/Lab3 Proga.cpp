#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

char symb(int N);
void makems(int** mm, int k, int kk, int** ms);
void lout(int** mm, int k, int kk, int* r, int iii);

int minv(int* d, int n, bool* ll);
void routeout(int* qq, int ss, int a, int v, int* r, int& iii);

int main()
{
	string fff = "";
	ifstream file("input.txt");
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
	cout << " Labyrinth vertices: " << endl;
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < kk; j++)
		{
			cout << setw(6) << mm[i][j] << setw(6);
		}
		cout << "\n";
	}
	int** ms = new int* [ss];
	for (int i = 0; i < ss; i++)
	{
		ms[i] = new int[ss];
		for (int j = 0; j < ss; j++) ms[i][j] = INT_MAX;
	}
	makems(mm, k, kk, ms);
	cout << endl;
	int x, y;
	cout << " Print start vertex: ";	cin >> x;
	if (x > ss || x <= 0) { cout << " [!] Wrond number!"; return 1; }
	cout << endl;
	cout << " Print finish vertex: ";	cin >> y;	
	if (y > ss || y <= 0) { cout << " [!] Wrond number!"; return 1; }
	x--;
	y--;
	int* d = new int[ss];
	bool* ll = new bool[ss];
	for (int i = 0; i < ss; i++) { d[i] = INT_MAX; ll[i] = false; }
	d[x] = 0;
	int* qq = new int[ss];
	for (int i = 0; i < ss; i++) qq[i] = 0;
	int vv = x, vso = 1;
	while (vso > 0)
	{
		vv = minv(d, ss, ll);
		ll[vv] = true;
		for (int i = 0; i < ss; i++)
		{
			if (ms[vv][i] == 1 && ll[i] == false)
			{
				if (d[i] > d[vv] + 1)
				{
					d[i] = d[vv] + 1;
					qq[i] = vv+1;
					vso++;
				}
			}
		}
		vso--;
	}
	int* r = new int[ss];
	int iii = 0;
	//for (int i = 0; i < ss; i++) { cout << d[i] << " " << i+1 << " " << qq[i] << endl; }
	routeout(qq, ss, x, y, r, iii);
	cout << "\n";
	lout(mm, k, kk, r, iii);
	return 0;
}

void routeout(int* qq, int ss, int a, int v, int* r, int& iii)
{
	int kk = v + 1;
	r[0] = kk;
	while (kk != a + 1 && iii < ss && kk>0)
	{
		iii++;
		kk = qq[kk - 1];
		r[iii] = kk;
	}
	if (kk != 0)
	{
		cout << "\n Our route: " << r[iii];
		for (int i = iii - 1; i >= 0; i--) cout << "->" << r[i];
	}
	else cout << " [!] No way from first vertex to finish";
	cout << "\n";
}
int minv(int* d, int ss, bool* ll)
{
	int min = INT_MAX;
	int ir = -1;
	for (int i = 0; i < ss; i++) if (min > d[i] && ll[i] == false) { min = d[i]; ir = i; }
	return ir;
}
void makems(int** mm, int k, int kk, int** ms)
{
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < kk; j++)
		{
			if (mm[i][j] >= 1)
			{
				if (i - 1 >= 0) if (mm[i - 1][j] >= 1) { ms[mm[i - 1][j]-1][mm[i][j]-1] = 1; ms[mm[i][j]-1][mm[i - 1][j]-1] = 1; }
				if (j - 1 >= 0) if (mm[i][j - 1] >= 1) { ms[mm[i][j - 1]-1][mm[i][j]-1] = 1; ms[mm[i][j]-1][mm[i][j - 1]-1] = 1; }
				if (i + 1 < k) if (mm[i + 1][j] >= 1) { ms[mm[i + 1][j]-1][mm[i][j]-1] = 1; ms[mm[i][j]-1][mm[i + 1][j]-1] = 1; }
				if (j + 1 < kk) if (mm[i][j + 1] >= 1) { ms[mm[i][j + 1]-1][mm[i][j]-1] = 1; ms[mm[i][j]-1][mm[i][j + 1]-1] = 1; }
			}
		}
	}
}
//char symb(int N)
//{
//	while (N > 60)
//	{
//		N -= 61;
//	}
//	if (N == 0) return '!';//start
//	else if (N < 10) return N + 48;
//	else if (N + 87 <= 122) return N + 87;
//	else if (N + 29 <= 87) return N + 29; //для - 'X'
//	else if (N + 30 <= 90) return N + 30;
//	return '+';
//}
char symb(int N)
{
	while (N > 8)
	{
		N -= 9;
	}
	switch (N)
	{
	case 0: return 'M';
	case 1: return 'a';
	case 2: return 'k';
	case 3: return 's';
	case 4: return '-';
	case 5: return 'L';
	case 6: return 'O';
	case 7: return 'H';
	case 8: return '-';
	}
	return '+';
}
void lout(int** mm, int k, int kk, int* r, int iii)
{
	ofstream fout;
	fout.open("output.txt");
	int h;
	for (int i = 0; i < k; i++)
	{
		cout << "\n | ";
		for (int j = 0; j < kk; j++)
		{
			h = -1;
			for (int hh = 0; hh <= iii; hh++)
			{
				if (mm[i][j] == r[hh]) { h = iii-hh; break; }
			}
			if (h!=-1) { cout << symb(h) << " ";	fout << symb(h) << " "; }
			else
			{
				if (mm[i][j] == 0) { cout << "X ";	fout << "X "; }
				else { cout << "  ";  fout << "  "; }
			}
		}
		fout << endl;
		cout << "|";
	}
}