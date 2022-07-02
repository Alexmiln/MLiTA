#include <fstream>

using namespace std;

int comp(const int*, const int*);



int main()
{
	int n = 0;
	int count[50];
	int prices[50];

	ifstream input("input.txt");
	ofstream output("output.txt");
	

	input >> n;
	for (int i = 0; i < n; i++)
	{
		input >> count[i];
	}
	for (int i = 0; i < n; i++)
	{
		input >> prices[i];
	}

	qsort(count, n, sizeof(int), (int (*)(const void*, const void*))comp);
	qsort(prices, n, sizeof(int), (int (*)(const void*, const void*))comp);

	int Max = 0;
	int Min = 0;

	int price = 0;
	for (int i = 0; i < n; i++)
	{
		Max += count[i] * prices[i];
		Min += count[i] * prices[n - i - 1];
	}

	output << Min << ' ' << Max << std::endl;

	return 0;
}

int comp(const int* i, const int* j)
{
	return *i - *j;
}