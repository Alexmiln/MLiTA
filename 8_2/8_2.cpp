/*Милютин Александр, ПС-24, задача 8.2, среда разработки Visual Studio 2022*/

/*
  8.2 Простые примеры на перестановки (6)

  Составить программы для решения следующих задач:
  1. решить уравнение на перестановках вида A × X = B,  где A и B - заданные перестановки, а X - неизвестная перестановка;
  2. по заданной перестановке из N элементов выдать K следующих перестановок в лексикографическом порядке;
  3. по заданной перестановке построить вектор  инверсий, а по вектору инверсий восстановить перестановку;
  4. перечислить перестановки из N элементов путем транспозиции смежных элементов с рекурсией и без нее.
  Входные данные задавать с клавиатуры, вывод результатов - на экран.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


typedef vector<int> Transposition;

istream& operator>>(istream& in, Transposition& p) {
	for (int i = 0; i < p.size(); i++) {
		in >> p[i];
		p[i];
	}
	return in;
}

ostream& operator<<(ostream& out, vector<int> const& p) {
	for (int i = 0; i < p.size(); i++) {
		out << p[i] << ' ';
	}
	return out;
}

Transposition invert(Transposition const& p) {
	Transposition inv(p.size());
	for (int i = 0; i < p.size(); i++) {
		inv[p[i] - 1] = i + 1;
	}
	return inv;
}

Transposition operator*(Transposition const& a, Transposition const& b) {
	Transposition p(a.size());
	for (int i = 0; i < a.size(); i++) {
		p[i] = b[a[i] - 1];
	}
	return p;
}

void task1() {
	int n;
	cout << "N = "; cin >> n;
	Transposition a(n), b(n);
	cout << "A = "; cin >> a;
	cout << "B = "; cin >> b;

	auto x = invert(a) * b;
	cout << x << endl;
}

void nextTransposition(Transposition& p) {
	for (int i = p.size() - 2; i >= 0; i--) {
		if (p[i] < p[i + 1]) {
			int mj = i + 1;
			for (int j = mj; j < p.size(); j++) {
				if (p[j] < p[i]) {
					continue;
				}
				if (p[j] < p[mj]) {
					mj = j;
				}
			}
			swap(p[i], p[mj]);
			reverse(p.begin() + i + 1, p.end());
			return;
		}
	}

	reverse(p.begin(), p.end());
}

void task2() {
	int n, k;
	cout << "N = "; cin >> n;
	Transposition a(n);
	cout << "A = "; cin >> a;
	cout << "K = "; cin >> k;

	for (int i = 0; i < k; i++) {
		nextTransposition(a);
		cout << a << endl;
	}
}

vector<int> inversionVector(Transposition const& p) {
	vector<int> v(p.size());
	for (int i = 1; i < p.size(); i++) {
		for (int j = 0; j < i; j++) {
			if (p[j] > p[i]) {
				v[i]++;
			}
		}
	}
	return v;
}

Transposition TranspositionFromInversionVector(vector<int> const& v) {
	vector<int> numbers;
	for (int i = 1; i <= v.size(); i++) {
		numbers.push_back(i);
	}

	Transposition p(v.size());
	for (int i = v.size() - 1; i >= 0; i--) {
		auto it = numbers.end() - 1 - v[i];
		p[i] = *it;
		numbers.erase(it, it + 1);
	}

	return p;
}

void task3() {
	int n;
	cout << "N = "; cin >> n;
	Transposition a(n);
	cout << "A = "; cin >> a;

	auto v = inversionVector(a);
	cout << "V = " << v << endl;

	a = TranspositionFromInversionVector(v);
	cout << "A = "; cout << a << endl;
}

vector<Transposition> allTranspositions(int n) {
	vector<Transposition> Transpositions{ {1} };

	for (int m = 2; m <= n; m++) {
		vector<Transposition> newTranspositions;
		newTranspositions.reserve(Transpositions.size() * m);
		for (int i = 0; i < Transpositions.size(); i++) {
			for (int j = 0; j < m; j++) {
				auto p = Transpositions[i];
				if (i % 2) {
					p.insert(p.begin() + j, m);
				}
				else {
					p.insert(p.end() - j, m);
				}
				newTranspositions.push_back(move(p));
			}
		}
		Transpositions = move(newTranspositions);
	}

	return Transpositions;
}

void allTranspositionsRecursiveImpl(int n, int m, int i, Transposition const& currentTransposition, vector<Transposition>& Transpositions) {
	if (m > n) {
		Transpositions.push_back(currentTransposition);
		return;
	}

	for (int j = 0; j < m; j++) {
		auto p = currentTransposition;
		if (i % 2) {
			p.insert(p.begin() + j, m);
		}
		else {
			p.insert(p.end() - j, m);
		}
		allTranspositionsRecursiveImpl(n, m + 1, i * m + j, p, Transpositions);
	}
}

vector<Transposition> allTranspositionsRecursive(int n) {
	vector<Transposition> Transpositions;

	allTranspositionsRecursiveImpl(n, 2, 0, { 1 }, Transpositions);

	return Transpositions;
}

void task4() {
	int n;
	cout << "N = "; cin >> n;

	cout << "1 - без рекурсии\n";
	cout << "2 - с рекурсией\n";
	int m;
	cout << "> ";  cin >> m;

	vector<Transposition> v;
	if (m == 1) {
		v = allTranspositions(n);
	}
	else if (m == 2) {
		v = allTranspositionsRecursive(n);
	}
	else {
		return;
	}

	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << endl;
	}
}

void printMenu() {
	cout << "0 - выход\n";
	cout << "1 - A * X = B\n";
	cout << "2 - K следующих перестановок\n";
	cout << "3 - вектор инверсий\n";
	cout << "4 - перестановки путем транспозиций\n";
	cout << "> ";
}

int main() {
	while (true) {
		printMenu();

		int n;
		cin >> n;
		switch (n) {
		case 1:
			task1();
			break;
		case 2:
			task2();
			break;
		case 3:
			task3();
			break;
		case 4:
			task4();
			break;
		case 0:
			return 0;
		}
	}
}
