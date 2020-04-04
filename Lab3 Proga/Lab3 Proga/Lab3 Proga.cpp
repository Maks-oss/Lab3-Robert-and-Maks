#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

char symb(int N);
void makems(int** mm, int k, int kk, int** ms);
void file_out(int** mm, int k, int kk);

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
	cout << "Labyrinth nodes: " << endl;
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < kk; j++)
		{
			cout << setw(6) << mm[i][j] << setw(6);
		}
		cout << "\n";
	}

	int** ms = new int* [ss];
	for (int i = 0; i < ss + 1; i++) ms[i] = new int[ss];

	for (int i = 0; i < ss; i++)
	{
		for (int j = 0; j < ss; j++)
		{
			ms[i][j] = 0;
		}
	}
	makems(mm, k, kk, ms);
	cout << endl;
	int x, y;
	cout << " Print start vertex: ";	cin >> x;
	if (x > ss || x <= 0) { cout << " [!] Wrond number!"; return 1; }
	cout << endl;
	cout << " Print finish vertex: ";		cin >> y;	
	if (y > ss || y <= 0) { cout << " [!] Wrond number!"; return 1; }

	cout << "\n";
	file_out(mm, k, kk);
	return 0;
}
void makems(int** mm, int k, int kk, int** ms)
{
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < kk; j++)
		{
			if (mm[i][j] >= 1)
			{
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
void file_out(int** mm, int k, int kk)
{
	ofstream fout;
	fout.open("output.txt");
	for (int i = 0; i < k; i++)
	{
		cout << "\n | ";
		for (int j = 0; j < kk; j++)
		{
			if (mm[i][j] == 0) { cout << "X ";	fout << "X "; }
			else { cout << "  ";  fout << "  "; }
		}
		fout << endl;
		cout << "|";
	}
}
