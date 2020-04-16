#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;


struct Vert
{
	bool ll; //відвідана?
	double pr, d; // координатна відстань від кінцевої верш; мінімальна відстань до початкової верш.
	int pri, vi, vj, qq; // номер вершини; x координата; y координата; номер предка
};

struct Route { int r; }; // номер вершини (утв наш шлях)

char symb(int N);
void makems(int** mm, int k, int kk, int** ms);
void lout(int** mm, int k, int kk, Route* routet, int iii);

int nextv(Vert* vert, int n);
void routeout(Route* route, Vert* vert, int ss, int a, int v, int& iii);

void endcord(int** mm, int k, int kk, int y, int& iend, int& jend);
void distv(int** mm, int k, int kk, Vert* vert, int iend, int jend);
void distsort(Vert* vert, int ss);
void A(int x, int ss, Vert* vert, int** ms);

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
	Vert* vert = new Vert[ss];						////////////////
	Route* route = new Route[ss];					////////////////
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
	for (int i = 0; i < ss; i++) { vert[i].d = INT_MAX; vert[i].ll = false; }
	vert[x].d = 0;
	for (int i = 0; i < ss; i++) vert[i].qq = 0;
	int iend, jend;
	endcord(mm, k, kk, y, iend, jend);
	distv(mm, k, kk, vert, iend, jend);
	for (int i = 0; i < ss; i++) vert[i].pri = i;
	distsort(vert, ss);
	A(x, ss, vert, ms);
	int iii = 0;
	routeout(route, vert, ss, x, y, iii);
	if (route[iii].r != 0) lout(mm, k, kk, route, iii);
	return 0;
}

void A(int x, int ss, Vert* vert, int** ms)
{
	int vv = x;
	while (vv != -1)
	{
		vert[vv].ll = true;
		for (int i = 0; i < ss; i++)
		{
			if (ms[vv][vert[i].pri] == 1 && vert[vert[i].pri].ll == false)
			{
				if (vert[vert[i].pri].d > vert[vv].d + sqrt(pow(vert[vv].vi - vert[vert[i].pri].vi, 2) + pow(vert[vv].vj - vert[vert[i].pri].vj, 2)))
				{
					vert[vert[i].pri].d = vert[vv].d + sqrt(pow(vert[vv].vi - vert[vert[i].pri].vi, 2) + pow(vert[vv].vj - vert[vert[i].pri].vj, 2));
					vert[vert[i].pri].qq = vv + 1;
				}
			}
		}
		vv = nextv(vert, ss);
	}
}
void distsort(Vert* vert, int ss)
{
	double hpr;
	int hppr;
	for (int i = 0; i < ss - 1; i++)
	{
		for (int j = i; j < ss; j++)
		{
			if (vert[i].pr > vert[j].pr)
			{
				hpr = vert[i].pr;
				vert[i].pr = vert[j].pr;
				vert[j].pr = hpr;

				hppr = vert[i].pri;
				vert[i].pri = vert[j].pri;
				vert[j].pri = hppr;
			}
		}
	}
}
void distv(int** mm, int k, int kk, Vert* vert, int iend, int jend)
{
	int ss = 0;
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < kk; j++)
		{
			if (mm[i][j] >= 1)
			{
				vert[ss].pr = sqrt(pow(iend - i, 2) + pow(jend - j, 2));
				vert[ss].vi = i;
				vert[ss].vj = j;
				ss++;
			}
		}
	}
}
void endcord(int** mm, int k, int kk, int y, int& iend, int& jend)
{
	bool vso = false;
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < kk; j++)
		{
			if (mm[i][j] - 1 == y)
			{
				iend = i;
				jend = j;
				vso = true;
			}
		}
		if (vso == true) break;
	}
}
void routeout(Route* route, Vert* vert, int ss, int a, int v, int& iii)
{
	int kk = v + 1;
	route[0].r = kk;
	while (kk != a + 1 && iii < ss && kk>0)
	{
		iii++;
		kk = vert[kk - 1].qq;
		route[iii].r = kk;
	}
	if (kk != 0)
	{
		cout << "\n Our route: " << route[iii].r;
		for (int i = iii - 1; i >= 0; i--) cout << "->" << route[i].r;
	}
	else cout << "\n [!] No way from first vertex to finish";
}
int nextv(Vert* vert, int ss)
{
	for (int i = 0; i < ss; i++) if (INT_MAX != vert[vert[i].pri].d && vert[vert[i].pri].ll == false) { return vert[i].pri; }
	return -1;
}
void makems(int** mm, int k, int kk, int** ms)
{
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < kk; j++)
		{
			if (mm[i][j] >= 1)
			{
				//if (j + 1 < kk && i + 1 < k) if (mm[i + 1][j + 1] >= 1) { ms[mm[i + 1][j + 1] - 1][mm[i][j] - 1] = 1; ms[mm[i][j] - 1][mm[i + 1][j + 1] - 1] = 1; }
				//if (j - 1 >= 0 && i - 1 >= 0) if (mm[i - 1][j - 1] >= 1) { ms[mm[i][j] - 1][mm[i - 1][j - 1] - 1] = 1; ms[mm[i - 1][j - 1] - 1][mm[i][j] - 1] = 1; }
				//if (j - 1 >= 0 && i + 1 < k) if (mm[i + 1][j - 1] >= 1) { ms[mm[i][j] - 1][mm[i + 1][j - 1] - 1] = 1; ms[mm[i + 1][j - 1] - 1][mm[i][j] - 1] = 1; }
				//if (i - 1 >= 0 && j + 1 < kk) if (mm[i - 1][j + 1] >= 1) { ms[mm[i][j] - 1][mm[i - 1][j + 1] - 1] = 1; ms[mm[i - 1][j + 1] - 1][mm[i][j] - 1] = 1; }

				if (i - 1 >= 0) if (mm[i - 1][j] >= 1) { ms[mm[i - 1][j] - 1][mm[i][j] - 1] = 1; ms[mm[i][j] - 1][mm[i - 1][j] - 1] = 1; }
				if (j - 1 >= 0) if (mm[i][j - 1] >= 1) { ms[mm[i][j - 1] - 1][mm[i][j] - 1] = 1; ms[mm[i][j] - 1][mm[i][j - 1] - 1] = 1; }
				if (i + 1 < k) if (mm[i + 1][j] >= 1) { ms[mm[i + 1][j] - 1][mm[i][j] - 1] = 1; ms[mm[i][j] - 1][mm[i + 1][j] - 1] = 1; }
				if (j + 1 < kk) if (mm[i][j + 1] >= 1) { ms[mm[i][j + 1] - 1][mm[i][j] - 1] = 1; ms[mm[i][j] - 1][mm[i][j + 1] - 1] = 1; }
			}
		}
	}
}
char symb(int N)
{
	while (N > 60)
	{
		N -= 61;
	}
	if (N == 0) return '!';//start
	else if (N < 10) return N + 48;
	else if (N + 87 <= 122) return N + 87;
	else if (N + 29 <= 87) return N + 29; //для - 'X'
	else if (N + 30 <= 90) return N + 30;
	return '?';
}
void lout(int** mm, int k, int kk, Route* route, int iii)
{
	ofstream fout;
	fout.open("output.txt");
	int h;
	cout << "\n";
	for (int i = 0; i < k; i++)
	{
		cout << "\n | ";
		for (int j = 0; j < kk; j++)
		{
			h = -1;
			for (int hh = 0; hh <= iii; hh++)
			{

				if (mm[i][j] == route[hh].r) { h = iii - hh; break; }
			}
			if (h != -1) { cout << symb(h) << " ";	fout << symb(h) << " "; }
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