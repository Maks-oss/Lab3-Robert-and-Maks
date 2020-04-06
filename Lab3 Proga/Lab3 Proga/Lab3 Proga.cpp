#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

char symb(int N);
void makems(int** mm, int k, int kk, int** ms);
void lout(int** mm, int k, int kk, int* r, int iii);

int minv(double* d, int n, bool* ll, int* pri);
void routeout(int* qq, int ss, int a, int v, int* r, int& iii);

void endcord(int** mm, int k, int kk, int y, int& iend, int& jend);
void distv(int** mm, int k, int kk, int* vi, int* vj, double* pr, int iend, int jend);
void distsort(double* pr, int* pri, int ss);
void A(int x, double* d, int ss, bool* ll, int* pri, int* vi, int* vj, int** ms, int* qq);

class Queue
{
private:
	int* pri;
	double* d;
	int ss;
	bool* ll;
public:
	Queue(int size);
	int minv();
	/*{
		double min = INT_MAX;
		int ir = -1;
		for (int i = 0; i < ss; i++) if (min >= d[pri[i]] + 2 && e[pri[i]] == false) { min = d[pri[i]]; ir = pri[i]; }
		return ir;
	}*/
};

Queue::Queue(int size)
{
	ss = size;
	ll = new bool[size];
	pri = new int[size];
	d = new double[size];
}
int Queue::minv()
{
	double min = INT_MAX;
	
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
	double* d = new double[ss];
	bool* ll = new bool[ss];
	for (int i = 0; i < ss; i++) { d[i] = INT_MAX; ll[i] = false; }
	d[x] = 0;
	int* qq = new int[ss];
	for (int i = 0; i < ss; i++) qq[i] = 0;
	int iend, jend;
	endcord(mm, k, kk, y, iend, jend);
	double* pr = new double[ss];
	int* vi = new int[ss];
	int* vj = new int[ss];
	distv(mm, k, kk, vi, vj, pr, iend, jend);
	int* pri = new int[ss];
	for (int i = 0; i < ss; i++) pri[i] = i;
	distsort(pr, pri, ss);
	A(x, d, ss, ll, pri, vi, vj, ms, qq);
	int* r = new int[ss];
	int iii = 0;
	routeout(qq, ss, x, y, r, iii);
	if(r[iii] != 0) lout(mm, k, kk, r, iii);
	return 0;
}

void A(int x, double*d, int ss, bool* ll, int* pri, int* vi, int* vj, int**ms, int* qq)
{
	int vv = x;
	while (vv != -1)
	{
		ll[vv] = true;
		for (int i = 0; i < ss; i++)
		{
			if (ms[vv][pri[i]] == 1 && ll[pri[i]] == false)
			{
				if (d[pri[i]] > d[vv] + sqrt(pow(vi[vv] - vi[pri[i]], 2) + pow(vj[vv] - vj[pri[i]], 2)))
				{
					d[pri[i]] = d[vv] + sqrt(pow(vi[vv] - vi[pri[i]], 2) + pow(vj[vv] - vj[pri[i]], 2));
					qq[pri[i]] = vv + 1;
					
				}
			}
		}
		vv = minv(d, ss, ll, pri);
	}
}
void distsort(double*pr, int*pri, int ss)
{
	double hpr;
	int hppr;
	for (int i = 0; i < ss-1; i++)
	{
		for (int j = i; j < ss; j++)
		{
			if (pr[i] > pr[j])
			{
				hpr = pr[i];
				pr[i] = pr[j];
				pr[j] = hpr;

				hppr = pri[i];
				pri[i] = pri[j];
				pri[j] = hppr;
			}
		}
	}
	//for (int i = 0; i < ss; i++) cout << pri[i] << " " << pr[i] << endl;
}
void distv(int**mm, int k, int kk, int* vi, int* vj, double* pr, int iend, int jend)
{
	int ss = 0;
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < kk; j++)
		{
			if (mm[i][j] >= 1)
			{
				pr[ss] = sqrt(pow(iend - i, 2) + pow(jend - j, 2));
				vi[ss] = i;
				vj[ss] = j;
				ss++;
			}
		}
	}
}
void endcord(int** mm, int k, int kk, int y, int& iend, int& jend)
{
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < kk; j++)
		{
			if (mm[i][j]-1 == y)
			{
				iend = i;
				jend = j;
			}
		}
	}
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
	else cout << "\n [!] No way from first vertex to finish";
}
//int minv(double* d, int ss, bool* ll, int* pri)
//{
//	double min = INT_MAX;
//	int ir = -1;
//	for (int i = 0; i < ss; i++) if (min >= d[pri[i]]+2 && ll[pri[i]] == false) { min = d[pri[i]]; ir = pri[i]; }
//	return ir;
//}
void makems(int** mm, int k, int kk, int** ms)
{
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < kk; j++)
		{
			if (mm[i][j] >= 1)
			{
				if (j + 1 < kk && i + 1 < k) if (mm[i + 1][j + 1] >= 1) { ms[mm[i + 1][j + 1] - 1][mm[i][j] - 1] = 1; ms[mm[i][j] - 1][mm[i + 1][j + 1] - 1] = 1; }
				if (j - 1 >= 0 && i - 1 >= 0) if (mm[i - 1][j - 1] >= 1) { ms[mm[i][j] - 1][mm[i - 1][j - 1] - 1] = 1; ms[mm[i - 1][j - 1] - 1][mm[i][j] - 1] = 1; }
				if (j - 1 >= 0 && i + 1 < k) if (mm[i + 1][j - 1] >= 1) { ms[mm[i][j] - 1][mm[i + 1][j - 1] - 1] = 1; ms[mm[i + 1][j - 1] - 1][mm[i][j] - 1] = 1; }
				if (i - 1 >= 0 && j + 1 < kk) if (mm[i - 1][j + 1] >= 1) { ms[mm[i][j] - 1][mm[i - 1][j + 1] - 1] = 1; ms[mm[i - 1][j + 1] - 1][mm[i][j] - 1] = 1; }

				if (i - 1 >= 0) if (mm[i - 1][j] >= 1) { ms[mm[i - 1][j]-1][mm[i][j]-1] = 1; ms[mm[i][j]-1][mm[i - 1][j]-1] = 1; }
				if (j - 1 >= 0) if (mm[i][j - 1] >= 1) { ms[mm[i][j - 1]-1][mm[i][j]-1] = 1; ms[mm[i][j]-1][mm[i][j - 1]-1] = 1; }
				if (i + 1 < k) if (mm[i + 1][j] >= 1) { ms[mm[i + 1][j]-1][mm[i][j]-1] = 1; ms[mm[i][j]-1][mm[i + 1][j]-1] = 1; }
				if (j + 1 < kk) if (mm[i][j + 1] >= 1) { ms[mm[i][j + 1]-1][mm[i][j]-1] = 1; ms[mm[i][j]-1][mm[i][j + 1]-1] = 1; }
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
	return '+';
}
//char symb(int N)
//{
//	while (N > 8)
//	{
//		N -= 9;
//	}
//	switch (N)
//	{
//	case 0: return 'M'; 
//	case 1: return 'a';
//	case 2: return 'k';
//	case 3: return 's';
//	case 4: return '-';
//	case 5: return 'L';
//	case 6: return 'O';
//	case 7: return 'H';
//	case 8: return '-';
//	}
//	return '+';
//}
void lout(int** mm, int k, int kk, int* r, int iii)
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