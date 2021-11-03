#include <iostream>
#include <ctime>
#include <algorithm>
#include <chrono>
#include <thread>
#define _USE_MATH_DEFINES
#include <math.h>

#define SUCCESS 0
#define FAIL -1

#include <Windows.h>

double getCPUTime()
{
    FILETIME createTime;
    FILETIME exitTime;
    FILETIME kernelTime;
    FILETIME userTime;
    if (GetProcessTimes(GetCurrentProcess(),
        &createTime, &exitTime, &kernelTime, &userTime) != -1)
    {
        SYSTEMTIME userSystemTime;
        if (FileTimeToSystemTime(&userTime, &userSystemTime) != -1)
            return (double)userSystemTime.wHour * 3600.0 +
            (double)userSystemTime.wMinute * 60.0 +
            (double)userSystemTime.wSecond +
            (double)userSystemTime.wMilliseconds / 1000.0;
    }
}

struct point
{
    double x, y;
};

struct figure
{
    struct point *pts;
    int n;
};

typedef struct figure figure_t;
typedef struct point point_t;

int create_pts(figure_t &fig)
{
    fig.pts = new point_t[fig.n];
    if (!fig.pts)
        return FAIL;
    return SUCCESS;
}

void delete_pts(figure_t &fig)
{
    delete fig.pts;
}

void input_pts(figure_t& fig)
{
    for (int i = 0; i < fig.n; i++)
        std::cin >> fig.pts[i].x >> fig.pts[i].y;
}

void output_pts(figure_t fig)
{
    for (int i = 0; i < fig.n; i++)
        std::cout << fig.pts[i].x << " " << fig.pts[i].y << std::endl;
}

void fill_pts(figure_t& fig)
{
    for (int i = 0; i < fig.n; i++)
    {
        fig.pts[i].x = double(std::rand() % 100) + 1;
        fig.pts[i].y = double(std::rand() % 100) + 1;
    }
}

double degrees_to_rad(double angle)
{
    return angle * M_PI / 180.0;
}

void point_rotate(point_t& point, double angle)
{
    double tmp_x = point.x;
    point.x = point.x * cos(angle) - point.y * sin(angle);
    point.y = tmp_x * sin(angle) + point.y * cos(angle);
}

int rot(figure_t &fig, double fi, int fl)
{
    double angle_pi = degrees_to_rad(fi);
    for (int i = 0; i < fig.n; ++i)
        point_rotate(fig.pts[i], angle_pi);
    return SUCCESS;
}

void rot_part(figure_t& fig, double fi, int start_pt, int end_pt)
{
    for (int i = start_pt; i < end_pt; i++)
        point_rotate(fig.pts[i], fi);
}

int rot_paral(figure_t& fig, double fi, int t_count)
{
    auto* threads = new std::thread[t_count];

    double angle_pi = degrees_to_rad(fi);

    int pts_per_t = fig.n / t_count;  // сколько точек обрабатывает один поток
    int start_pt = 0, end_pt;
    for (int i = 0; i < t_count - 1; i++)
    {
        // каждому потоку делегируем срез со start_row по end_row
        start_pt = i * pts_per_t;
        end_pt = (i + 1) * pts_per_t;
        threads[i] = std::thread(rot_part, std::ref(fig), angle_pi, start_pt, end_pt);
    }
    threads[t_count - 1] = std::thread(rot_part, std::ref(fig), angle_pi, (t_count - 1) * pts_per_t, fig.n);

    for (int i = 0; i < t_count; i++)
        threads[i].join();

    return SUCCESS;
}

float get_time(int (*alg)(figure_t&, double, int), figure_t fig, int tcnt = 1, int itcnt = 1)
{
    fill_pts(fig);
    double fi = 45;
    auto start = getCPUTime();
    for (int i = 0; i < itcnt; i++)
        alg(fig, fi, tcnt);
    auto end = getCPUTime();

    auto duration = end - start;
    float time = duration * 1000000 / (double)itcnt;
    return time;
}

void analyse_time()
{
    figure_t fig;
    int t_counts[6] = { 1, 2, 4, 8, 16, 32 };
    int sizes[8] = { 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000 };

    float results[6][3];
    float results2[8][3];

    fig.pts = nullptr;
    int size = 8000;
    int iterations = 1000;
    fig.n = size;
    if (create_pts(fig) == SUCCESS)
    {
        int (*algs[2])(figure_t&, double, int) = { rot, rot_paral };

        for (int si = 0; si < 6; si++)
            for (int ai = 0; ai < 2; ai++)
            {
                results[si][ai] = get_time(algs[ai], fig, t_counts[si], iterations);
            }

        std::cout << "\nResults (number of points = 8000):" << std::endl;
        std::cout << std::endl;
        for (int i = 0; i < 6; i++)
        {
            std::cout << "Number of threads: " << t_counts[i] << std::endl;
            std::cout << std::endl;
            std::cout << "Linear alg: ";
            std::cout << results[i][0] << std::endl;
            std::cout << "Parallel alg: ";
            std::cout << results[i][1] << std::endl;
            std::cout << std::endl;
        }

        for (int si = 0; si < 8; si++)
            for (int ai = 0; ai < 2; ai++)
            {
                fig.n = sizes[si];
                results2[si][ai] = get_time(algs[ai], fig, 4, iterations);
            }

        std::cout << "\nResults (number of threads = 4):" << std::endl;
        std::cout << std::endl;
        for (int i = 0; i < 8; i++)
        {
            std::cout << "Number of points: " << sizes[i] << std::endl;
            std::cout << std::endl;
            std::cout << "Linear alg: ";
            std::cout << results2[i][0] << std::endl;
            std::cout << "Parallel alg: ";
            std::cout << results2[i][1] << std::endl;
            std::cout << std::endl;
        }
    }
    else
        std::cout << "Memory error" << std::endl;
}

void by_hand()
{
    figure_t fig, tmp;

    std::cout << "Input number of points: ";
    std::cin >> fig.n;

    if (fig.n <= 0)
    {
        std::cout << "Incorrect input!";
    }
    else
    {
        fig.pts = nullptr;
        double fi;
        if (create_pts(fig) == SUCCESS)
        {
            std::cout << "\nInput points (in format: x y): " << std::endl;
            input_pts(fig);
            std::cout << "\nInput angle of rotation (in degrees): ";
            std::cin >> fi;

            const char* alg_names[2] = { "linear rotation algorithm", "parallel rotation algorithm" };
            int (*algs[2])(figure_t&, double, int) = { rot, rot_paral };

            tmp.n = fig.n;
            create_pts(tmp);
            for (int i = 0; i < fig.n; ++i)
                tmp.pts[i] = fig.pts[i];
            rot(fig, fi, 2);
            std::cout << "\nResult of rotation with linear rotation algorithm :" << std::endl;
            output_pts(fig);

            rot_paral(tmp, fi, 2);
            std::cout << "\nResult of rotation with parallel rotation algorithm :" << std::endl;
            output_pts(tmp);

            delete_pts(tmp);
            delete_pts(fig);
        }
        else
        {
            std::cout << "Memory error" << std::endl;
        }
    }
}

int main()
{
    int choice = 1;
    while (choice != 0)
    {
        std::cout << "Menu: \n";
        std::cout << "1 - rotate \n";
        std::cout << "2 - measure time \n";
        std::cout << "0 - exit \n";
        std::cout << "Choice: ";
        std::cin >> choice;
        if (choice == 1)
            by_hand();
        else if (choice == 2)
            analyse_time();
    }
}