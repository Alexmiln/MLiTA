/*
Милютин Александр, ПС-24, задача 14.11, среда разработки Visual Studio 2022
*
14.11. Буйки (9)
*
На пляже перпендикулярно береговой линии размечены прямолинейными буйками параллельные плавательные дорожки. Они получились разной ширины. Требуется сдвинуть некоторые из буйков без изменения порядка их следования так, чтобы дорожки оказались равной ширины, а сумма сдвигов была минимальной.
Ввод. Первая строка содержит число буйков N (2 ≤ N ≤ 400). Во второй строке  указываются координаты буйков X1 < X2  <…< XN  (-10000 ≤  Xi  ≤  10000)  в виде целых чисел по оси X, совпадающей с береговой линией.
Вывод. В первой строке выводится с точностью до 4 знаков действительное число S – минимальная общая длина требуемых сдвигов. Во второй строке выводятся через пробел с точностью до 7 знаков новые координаты буйков. Если имеется несколько вариантов решения, вывести любое из них.
*
Пример
Ввод
4
-2 2 6 9
Вывод
1.0000
-2.0000000 1.6666667 5.3333333 9.0000000
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
    const string invalidNumberBuoys = "Incorrect number of buoys.\nPossible values: 2 <= N <= 400.\n";
    const string invalidCoordBuoy = "Incorrect coordinate of a buoy.\nPossible values: -10000 <= x <= 10000.\n";

    ifstream input("input.txt");
    ofstream output("output.txt");

    int N;
    input >> N;
    if (N < 2 || N > 400)
    {
        cout << invalidNumberBuoys;
        return 0;
    }

    vector<short int> Coord;

    for (int i = 0; i < N; ++i) {
        short int x;
        input >> x;
        if (x < -10000 || x > 10000)
        {
            cout << invalidCoordBuoy;
            return 0;
        }
        Coord.push_back(x);
    }


    //    for (const auto& i: Coord)
    //        std::cout << i << ' ';
    vector<int> Interval;
    for (int i = 0; i < N - 1; ++i)
    {
        int x;
        x = Coord[i + 1] - Coord[i];
        Interval.push_back(x);
    }

    int unS;
    unS = Coord[N - 1] - Coord[0];


    return 0;
}
