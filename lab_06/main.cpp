#include <iostream>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include "matrix.h"
#include <ctime>
#include <utility>
#include <chrono>
using namespace std;

using namespace std::chrono;

//рекурсивный алгоритм полного обхода
static int ss(0);
void brute_force(Matrix &D, vector<int> &min_path, int &min_d, vector<int> &cur_path,
                 vector<bool> &visited, int &cur_len);

pair<int, vector<int> > brute_force_find(Matrix D)
{
    int n = D.rows();
    vector<bool> visited(n, 0);
    vector<int> cur_path;
    vector<int> min_path;
    int cur_len = 0;
    int min_path_len = INT_MAX;
    for (int i = 0; i < n; i++)
    {
        cur_path.clear();
        cur_path.push_back(i);
        fill(visited.begin(), visited.end(), 0);
        visited[i] = 1;
        cur_len = 0;
        brute_force(D, min_path, min_path_len, cur_path, visited, cur_len);
    }
    return pair<int, vector<int>>(min_path_len, min_path);
}


void brute_force(Matrix &D, vector<int> &min_path, int &min_d, vector<int> &cur_path,
                 vector<bool> &visited, int &cur_len)
{
    size_t M = D.cols();
    if (cur_path.size() == M)
    {
        ss++;
        int tmp = D[cur_path.back()][cur_path[0]];
        if (cur_len + tmp < min_d)
        {
            min_path = cur_path;
            min_d = cur_len + tmp;
        }
        return;
    }
    for (size_t i = 0; i < M; i++)
    {
        if (!visited[i])
        {
           int tmp = D[cur_path.back()][i];
           if (cur_len + tmp > min_d)
               continue;
           cur_len += tmp;
           cur_path.push_back(i);
           visited[i] = 1;
           brute_force(D, min_path, min_d, cur_path, visited, cur_len);
           visited[i] = 0;
           cur_path.pop_back();
           cur_len -= tmp;
        }
    }
}

// Муравьиный алгоритм
pair<int, vector<int>> AntAlgorithm(Matrix D, const int Tmax, const double alpha, const double ro)
{
    const int teta_beg = 10;
    const int teta_min = 5;
    const size_t M = D.cols(); //количество вершин
    const double Q = D.avg() * M; //примерное значение длины пути
    const double betta = 1 - alpha;

    Matrix Attr(M, M); //присваивание видимости
    for (size_t i = 0; i < D.rows(); i++)
        for (size_t j = 0; j < D.cols(); j++)
        {
            double tmp = 1/D[i][j];
            Attr[i][j] = tmp;
            Attr[j][i] = tmp;
        }

    Matrix Teta(M, M, teta_beg); //феромоны
    Matrix Delta_Teta(M, M); //феромоны на текущем шаге

    int Lmin = -1; //длина кратчайшего маршрута
    vector<int> Lp; // кратчайший маршрут
    vector<double> P(M, 0.0); //вероятности

    double random_res;
    // цикл по времени жизни колонии
    for (int t = 0; t < Tmax; t++)
    {
        Delta_Teta.zero();
        //цикл по всем муравьям
        for (size_t k = 0; k < M; k++)
        {
            vector<int> cur_path;
            cur_path.push_back(k);
            int cur_path_length = 0;
            int i = k;
            //строим маршрут
            while (cur_path.size() < M)
            {
                vector<int> not_visited;
                // поиск всех непосещенных вершин
                bool nv = true;
                for (size_t i = 0; i < M; i++)
                {
                    nv = true;
                    for (size_t j = 0; j < cur_path.size(); j++)
                        if ((int)i == cur_path[j])
                            nv = false;
                    if (nv)
                        not_visited.push_back(i);
                }

                for (size_t j = 0; j < M ; j++)
                    P[j] = 0.0;
                // посчитаем вероятности
                for (size_t j = 0; j < not_visited.size(); j++)
                {
                    if (D[i][not_visited[j]])
                    {
                        double sum = 0;
                        for (auto n: not_visited)
                            sum += pow(Teta[i][n], alpha) * pow(Attr[i][n], betta);
                        P[j] = pow(Teta[i][not_visited[j]], alpha) * pow(Attr[i][not_visited[j]], betta)/sum;
                    }
                    else
                        P[j] = 0;
                }
                //бросается случайное число для выбора муравья
                random_res  = (rand() % 100) / 100.0;
                int best_p = 0;
                double sum_p = 0;
                for (size_t s = 0; s < M; s++)
                {
                    sum_p += P[s];
                    if(random_res < sum_p)
                    {
                        best_p = s;
                        break;
                    }
                }
                // добавим новый город в путь
                int new_town = not_visited[best_p];
                cur_path.push_back(new_town);
                cur_path_length += D[i][new_town];

                //обновим феромон на ребре
                Delta_Teta[i][new_town] += Q/cur_path_length;

                i = new_town; // дальше продолжим путь из этого города
                not_visited.erase(not_visited.begin()+best_p);
            }

            cur_path_length += D[cur_path[cur_path.size()-1]][k];
            // проверим не кратчайший ли это путь
            if (Lmin == -1 || cur_path_length < Lmin)
            {
                Lmin = cur_path_length;
                Lp = cur_path;
            }
        }

        //часть феромона должна испариться
        for (size_t ii = 0; ii < M; ii++)
            for (size_t jj = 0; jj < M; jj++)
            {
                Teta[ii][jj] = Teta[ii][jj] * (1.0 - ro) + Delta_Teta[ii][jj];
                if (Teta[ii][jj] < teta_min)
                    Teta[ii][jj] = teta_min;
            }
    }

    return pair<int, vector<int>>(Lmin, Lp);
}

void print_res(pair<int, vector<int>> results)
{
    cout << "\nMin path length = " << results.first << ";\nMin path is: ";
    for (int i = 0; i < results.second.size(); i++)
        cout << results.second[i] << " ";
    cout <<" \n";
}

int main()
{
    Matrix mat(4, 4);
    mat.make_rand();
    mat.print();


    pair<int, vector<int>> results = brute_force_find(mat);

    printf("\n=== Brute force algorithm ===");
    print_res(results);
    pair<int, vector<int>> res = AntAlgorithm(mat, 350, 0.75, 0.25);

    printf("\n=== Ant algorithm ===");
    print_res(res);


    return 0;
}
