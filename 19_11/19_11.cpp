/*Милютин Александр, ПС-24, задача 19.11, среда разработки Visual Studio 2022*/

/*19.11. Несчастливые билеты (2)
Автобусный билет состоит из 2N цифр (2 ≤ N ≤ 105) и может начинаться с нулей. Он считается несчастливым, если число, образованными цифрами первой половины номера, отличается в большую или меньшую сторону от числа из цифр второй половины номера на 13. Сколько всего несчастливых номеров?
Ввод из файла INPUT.TXT.  В единственной строке задается значение N. 
Вывод в файл OUTPUT.TXT. В единственной строке выводится количество несчастливых номеров.
Пример
Ввод
2
Вывод
174
*/


#include <fstream>
#include <string>
#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	int n = 0;

	ifstream input("input.txt");
	ofstream output("output.txt");

	if (!input)
	{
		cout << "input.txt not found\n";
		return 1;
	}

	input >> n;
	int count = (pow(10, n) - 13) * 2;

	output << count << std::endl;

	return 0;
}
