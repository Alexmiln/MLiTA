//  Милютин Александр, ПС-24, задача 19.21, среда разработки Visual Studio 2022
//
//  19.17. Игра в числа (3)
// 
//  Вася очень любит играть в числа. Для этой игры нужна колода из N различных целых чисел от 1 до N. 
//  Эдик только что достал новую колоду. Вася говорит, что в колоде недостает ровно двух чисел. 
//  Зная N (количество чисел, которое должно быть в колоде) и S (сумму имеющихся чисел), определите, не ошибся ли Вася, и если не ошибся, предложите, каких именно чисел недостает.
//  Ввод.В первой строке файла INPUT.TXT находятся два целых числа : N(3  N  104) и S.
//  Вывод.Если могли пропасть ровно два числа, в первой строке файла OUTPUT.TXT напишите YES, во второй - приведите возможный вариант – два числа через пробел.
//  Если решений несколько, выведите в порядке возрастания такие два числа, для которых абсолютная величина разности минимальна.Если Вася ошибся, в единственной строке напишите NO.
//
//  Примеры
//Ввод 1      Ввод 2
//6 13        6 12
//Вывод 1     Вывод 2
//YES         YES
//3 5         4 5

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
	ifstream input("input.txt");
	ofstream output("output.txt");

	if (!input)
	{
		cout << "input.txt not found\n";
		return 1;
	}

	int N, S;
	input >> N >> S;
	if (N < 3 || N > 10000)
	{
		cout << "Incorrect number of digits that should be in the deck.\nPossible values: 3 <= N <= 10000.\n";
		return 1;
	}

	if (S < 0)
	{
		cout << "Incorrect sum.\n";
		return 1;
	}

	unsigned int sumN;
	sumN = (N*(N + 1)) / 2;

	if (S == sumN)
	{
		output << "NO";
		return 0;
	}
	
	int temp = sumN - S;

	for (int i = 0; i < N+1; i++)
	{
		int diff = temp - i;
		if (diff <= N && diff != i && i != 0 && diff < i)
		{
			output << "YES\n" << diff << " " << i;
			return 0;
		}
	}

	output << "NO";
	return 0;
}