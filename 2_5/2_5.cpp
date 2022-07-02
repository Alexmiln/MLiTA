/*  Милютин Александр, ПС-24, задача 2.5, среда разработки Visual Studio 2022  */

/*2.5. Пчела Майя (6)
Пчелы живут в ульях, где есть соты. Соты представляют собой поле правильных шестиугольников, соприкасающихся друг с другом. Правильное поле строится следующим образом: 
сначала имеется всего одна сота (рис. 1) – это правильное поле первого уровня; 
затем вокруг соты появляются соседние (рис. 2) – это правильное поле второго уровня;
затем строится еще один «ободок» (рис. 3) – это правильное поле третьего уровня, и т. д.
Пчела Майя возвращается в улей. Она живет в одной из сот правильного поля уровня N (2 ≤ N ≤ 20). Для того, чтобы добраться до своей соты (если она не расположена с краю поля), 
Майе нужно переместиться через другие соты, в которых могут жить как друзья (перемещаться можно), так и враги (перемещаться нельзя). 
Майя очень устала и хочет добраться до своей соты, пройдя через минимальное число других сот. 
Свой путь она может начинать с любой дружественной соты, находящейся с краю поля (то есть такой соты, которая не окружена со всех сторон соседними сотами).
*/

/*Ввод. В первой строке файла INPUT.TXT записано одно число N – уровень правильного поля. В следующих 2N-1 строках содержатся последовательности из 
символов ‘V’, ‘D’, ‘M’ (‘V’ – сота врага, ‘D’ – сота друга, ‘M’ – сота Майи). 
Вывод. В единственной строке файла OUTPUT.TXT выводится минимальное число сот, через которые придется пройти Майе, чтобы попасть в свою соту (своя сота тоже считается), 
или ноль, если Майе не удастся попасть в свою соту.
Примеры
Ввод 1     Ввод 2     Ввод 3
2          3          2
VV         VVV        VV
VMV        VDDV       VMV
VD         VMVDV      VV
           VVDV
           VVD
Вывод 1    Вывод 2    Вывод 3
2          6          0
*/
#include <queue>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

struct CellCoord
{
    char type;
    int stepsCount = 0;
    bool isChecked = false;

    CellCoord* topL = nullptr;
    CellCoord* topR = nullptr;
    CellCoord* L = nullptr;
    CellCoord* R = nullptr;
    CellCoord* bottomL = nullptr;
    CellCoord* bottomR = nullptr;
};

void InitHive(vector<vector<CellCoord>>& hive, int N)
{
    int beeCount = 0;

    for (int i = 0; i < (2 * N - 1); i++)
    {
        vector<CellCoord> hiveLine;

        if (i < N)
        {
            beeCount = N + 1;
        }
        else
        {
            --beeCount;
        }

        for (int j = 0; j < beeCount; j++)
        {
            CellCoord cellCoord;
            hiveLine.push_back(cellCoord);
        }

        hive.push_back(hiveLine);
    }
}

void CreateLinksInHive(vector<vector<CellCoord>>& hive)
{
    size_t N = hive.front().size();
    size_t centerCoord = N - 1;

    for (size_t i = 0; i < centerCoord; i++)
    {
        for (size_t j = 0; j < hive[i].size(); j++)
        {
            hive[i][j].bottomL = &hive[i + 1][j];
            hive[i][j].bottomR = &hive[i + 1][j + 1];

            hive[i + 1][j].topR = &hive[i][j];
            hive[i + 1][j + 1].topL = &hive[i][j];

            if (j != 0)
            {
                hive[i][j].L = &hive[i][j - 1];
            }
            if (j != hive[i].size() - 1)
            {
                hive[i][j].R = &hive[i][j + 1];
            }
        }
    }

    for (size_t i = centerCoord; i < 2 * centerCoord; i++)
    {
        for (size_t j = 0; j < hive[i].size(); j++)
        {
            if (j != 0)
            {
                hive[i][j].bottomL = &hive[i + 1][j - 1];

                hive[i][j].L = &hive[i][j - 1];
            }
            if (j != hive[i].size() - 1)
            {
                hive[i][j].bottomR = &hive[i + 1][j];

                hive[i + 1][j].topL = &hive[i][j];
                hive[i + 1][j].topR = &hive[i][j + 1];

                hive[i][j].R = &hive[i][j + 1];
            }
        }
    }

    for (size_t i = 1; i < N; i++)
    {
        hive[2 * centerCoord][i].L = &hive[2 * centerCoord][i - 1];
    }
    for (size_t i = 0; i < N - 1; i++)
    {
        hive[2 * centerCoord][i].R = &hive[2 * centerCoord][i + 1];
    }
}

void ReadHive(ifstream& input, vector<vector<CellCoord>>& hive)
{
    string hiveLine;
    char type;

    for (size_t i = 0; i < hive.size(); i++)
    {
        getline(input, hiveLine);
        stringstream stream(hiveLine);

        for (size_t j = 0; j < hive[i].size(); j++)
        {
            stream >> type;
            hive[i][j].type = type;
        }
    }
}

const char ENEMY = 'V';
const char FRIEND = 'D';
const char MAYA = 'M';

void CheckCellCoord(queue<CellCoord*>& cellCoordsToCheck, CellCoord* cellCoord, bool& isFinish, int& finishStep)
{
    int step = cellCoord->stepsCount;

    if (cellCoord->type != ENEMY && !isFinish)
    {
        if (cellCoord->type != MAYA)
        {
            if (cellCoord->L && !cellCoord->L->isChecked)
            {
                cellCoord->L->stepsCount = step + 1;
                cellCoord->L->isChecked = true;
                cellCoordsToCheck.push(cellCoord->L);
            }
            if (cellCoord->R && !cellCoord->R->isChecked)
            {
                cellCoord->R->stepsCount = step + 1;
                cellCoord->R->isChecked = true;
                cellCoordsToCheck.push(cellCoord->R);
            }
            if (cellCoord->topL && !cellCoord->topL->isChecked)
            {
                cellCoord->topL->stepsCount = step + 1;
                cellCoord->topL->isChecked = true;
                cellCoordsToCheck.push(cellCoord->topL);
            }
            if (cellCoord->topR && !cellCoord->topR->isChecked)
            {
                cellCoord->topR->stepsCount = step + 1;
                cellCoord->topR->isChecked = true;
                cellCoordsToCheck.push(cellCoord->topR);
            }
            if (cellCoord->bottomL && !cellCoord->bottomL->isChecked)
            {
                cellCoord->bottomL->stepsCount = step + 1;
                cellCoord->bottomL->isChecked = true;
                cellCoordsToCheck.push(cellCoord->bottomL);
            }
            if (cellCoord->bottomR && !cellCoord->bottomR->isChecked)
            {
                cellCoord->bottomR->stepsCount = step + 1;
                cellCoord->bottomR->isChecked = true;
                cellCoordsToCheck.push(cellCoord->bottomR);
            }
        }
        else
        {
            finishStep = cellCoord->stepsCount;
            isFinish = true;
        }
    }
}

void MarkStepsFromCellCoord(CellCoord& cellCoord, int& finishStep)
{
    cellCoord.stepsCount = 1;

    queue<CellCoord*> cellCoordsToCheck;
    cellCoordsToCheck.push(&cellCoord);
    bool isFinish = false;

    while (!cellCoordsToCheck.empty())
    {
        CheckCellCoord(cellCoordsToCheck, cellCoordsToCheck.front(), isFinish, finishStep);
        cellCoordsToCheck.pop();
    }
}

int GetBestStepsCount(vector<vector<CellCoord>> const& hiveToSearch)
{
    auto hive = hiveToSearch;
    int finishStep = 0;

    for (size_t i = 0; i < hive.size(); i++)
    {
        for (size_t j = 0; j < hive[i].size(); j++)
        {
            if ((i == 0) ||
                (i == (hive.size() - 1)) ||
                (j == 0) ||
                (j == hive[i].size() - 1))
            {
                if (hive[i][j].type != ENEMY)
                {
                    MarkStepsFromCellCoord(hive[i][j], finishStep);

                    //if (finishStep == 39)
                    //{
                    //    WriteHive(hiveToSearch, false);
                    //}
                }
            }
        }
    }

    return finishStep;
}

int main()
{
    ifstream input("input.txt");
    ofstream output("output.txt");

    if (!input)
    {
        cout << "input.txt not found\n";
        return 1;
    }

    int N;
    input >> N;

    if (N < 2 || N > 20)
    {
        cout << "Incorrect number of levels.\nPossible values: 2 <= N <= 20.\n";
        return 1;
    }

    vector<vector<CellCoord>> hive;
    InitHive(hive, N);

    ReadHive(input, hive);
    CreateLinksInHive(hive);

    output << GetBestStepsCount(hive);

    return 0;
}
