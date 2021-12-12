#include <iostream>
#include <queue>
#include <thread>
#include <vector>
#include <mutex>
#include <cstdlib>
#include <string>
#include <ctime>
#include <algorithm>

#define INPUT_FAIL -1
#define SUCCESS 0
#define SIZE 50000

static clock_t start_t;

using namespace std;

class Object
{
public:
    Object(string str, int task_num, clock_t time)
    {
        this->str = str;
        this->task_num = task_num;
        this->time = time;
    }

    string str;
    int task_num;
    clock_t time;
};

static queue<Object> queue1;
static queue<Object> queue2;
static queue<Object> queue3;

static vector<string> objvec;
static vector<string> res;

static mutex m1, m2, m3, resm;

static int n;

class Timer
{
public:
    Timer() = default;
    ~Timer() = default;

    void set_size()
    {
        waiting_times.resize(n);
        working_times.resize(n);
        time_from_start.resize(n);

        for (int i = 0; i < n; i++)
        {
            waiting_times[i].resize(0);
            working_times[i].resize(0);
            time_from_start[i].resize(0);
        }
        min_time.resize(0);
        max_time.resize(0);
        avg_time.resize(0);
        proc_time.resize(0);
    }

    void add_time(bool is_waiting, clock_t time, int task)
    {
        if (is_waiting)
            waiting_times[task].push_back(time);
        else
            working_times[task].push_back(time);
    }

    void add_time_from_start(clock_t time, int task)
    {
        time_from_start[task].push_back(time);
    }

    void calculate()
    {

        for (size_t i = 0; i < waiting_times.size(); i++)
        {
            auto minmax = std::minmax_element(waiting_times[i].begin(), waiting_times[i].end());
            min_time.push_back(*minmax.first);
            max_time.push_back(*minmax.second);

            auto sum_of_el = 0;
            for (auto& c : waiting_times[i])
                sum_of_el += c;

            avg_time.push_back(sum_of_el / waiting_times[i].size());
        }

        for (size_t i = 0; i < working_times.size(); i++)
        {
            auto sum_of_el = 0;
            for (auto& c : working_times[i])
                sum_of_el += c;
            proc_time.push_back(sum_of_el);
        }
    }

    vector<vector<clock_t>> get_waiting_times()
    {
        return waiting_times;
    }

    vector<vector<clock_t>> get_working_times()
    {
        return working_times;
    }

    vector<clock_t> get_min_time()
    {
        return min_time;
    }

    vector<clock_t> get_max_time()
    {
        return max_time;
    }

    vector<clock_t> get_avg_time()
    {
        return avg_time;
    }

    vector<clock_t> get_proc_time()
    {
        return proc_time;
    }

    vector<vector<clock_t>> get_time_from_start()
    {
        return time_from_start;
    }

private:
    vector<vector<clock_t>> waiting_times;
    vector<vector<clock_t>> working_times;
    vector<vector<clock_t>> time_from_start;
    vector<clock_t> min_time;
    vector<clock_t> max_time;
    vector<clock_t> avg_time;
    vector<clock_t> proc_time;

};

static Timer timer;

// Диапазон чисел: [min, max]
int get_random_number(int min, int max)
{
    // Получить случайное число - формула
    int num = min + rand() % (max - min + 1);

    return num;
}

string generate(size_t size)
{
    string s = "";
    int reg = 0;
    int code = 0;  // ASCII код буквы (латиница)
    int min_low = 97;  // a
    int max_low = 122;  // z
    int min_upper = 65;  // A
    int max_upper = 90;  // Z
    for (size_t i = 0; i < size; i++)
    {
        reg = get_random_number(0, 1);
        if (reg)
            code = get_random_number(min_upper, max_upper);
        else
            code = get_random_number(min_low, max_low);
        s.push_back(code);
    }
    return s;
}

// сдвиг на следующую букву алфавита
string caesar(string s)
{
    for (size_t i = 0; i < s.length(); i++)
    {
        if (s[i] == 'z')
            s[i] = 'a';
        else if (s[i] == 'Z')
            s[i] = 'A';
        else
            s[i]++;
    }
    return s;
}

string upper_lower(string s)
{
    for (size_t i = 0; i < s.length(); i++)
    {
        if (islower(s[i]))
            s[i] = toupper(s[i]);
        else
            s[i] = tolower(s[i]);
    }
    return s;
}

string shift_str(string s)
{
    int shift = s.length() / 2;
    for (size_t i = 0; i < s.length() / 2; i++)
    {
        char st = s[i];
        s[i] = s[i + shift];
        s[i + shift] = st;
    }
    return s;
}

void first_conv()
{
    int num = 0;
    while (true)
    {
        if (num == n)
            break;
        m1.lock();
        if (queue1.empty())
        {
            m1.unlock();
            continue;
        }
        string cur_str = queue1.front().str;
        int cur_task_num = queue1.front().task_num;
        timer.add_time_from_start(clock() - start_t, cur_task_num);
        timer.add_time(1, clock() - queue1.front().time, queue1.front().task_num);
        queue1.pop();

        clock_t cur_time = clock();
        m1.unlock();
        string new_str = caesar(cur_str);
        m2.lock();
        timer.add_time_from_start(clock() - start_t, cur_task_num);
        timer.add_time(0, clock() - cur_time, cur_task_num);

        queue2.push(Object(new_str, cur_task_num, clock()));
        m2.unlock();
        num++;
    }
}

void second_conv()
{
    int num = 0;
    while (true)
    {
        if (num == n)
            break;
        m2.lock();
        if (queue2.empty())
        {
            m2.unlock();
            continue;
        }
        string cur_str = queue2.front().str;
        int cur_task_num = queue2.front().task_num;
        timer.add_time_from_start(clock() - start_t, cur_task_num);
        timer.add_time(1, clock() - queue2.front().time, queue2.front().task_num);
        queue2.pop();

        clock_t cur_time = clock();
        m2.unlock();
        string new_str = upper_lower(cur_str);
        m3.lock();
        timer.add_time_from_start(clock() - start_t, cur_task_num);
        timer.add_time(0, clock() - cur_time, cur_task_num);

        queue3.push(Object(new_str, cur_task_num, clock()));
        m3.unlock();
        num++;
    }
}

void third_conv()
{
    int num = 0;
    while (true)
    {
        if (num == n)
            break;
        m3.lock();
        if (queue3.empty())
        {
            m3.unlock();
            continue;
        }
        string cur_str = queue3.front().str;
        int cur_task_num = queue3.front().task_num;
        timer.add_time_from_start(clock() - start_t, cur_task_num);
        timer.add_time(1, clock() - queue3.front().time, queue3.front().task_num);
        queue3.pop();

        clock_t cur_time = clock();
        m3.unlock();
        string new_str = shift_str(cur_str);
        resm.lock();
        timer.add_time_from_start(clock() - start_t, cur_task_num);
        timer.add_time(0, clock() - cur_time, cur_task_num);

        res.push_back(new_str);
        resm.unlock();
        num++;
    }
}

void create_log(clock_t time, char* fname) {
    FILE* f;
    f = fopen(fname, "w");
    timer.calculate();
    for (int i = 0; i < n; i++) {
        fprintf(f, "Строка № %d\n", i + 1);
        fprintf(f, "Время ожидания в первой очереди: %ld\n", timer.get_waiting_times()[i][0]);

        fprintf(f, "Время начала работы первого контейнера (с момента старта программы): %ld\n", timer.get_time_from_start()[i][0]);
        fprintf(f, "Время работы первого контейнера: %ld\n", timer.get_working_times()[i][0]);

        fprintf(f, "Время помещения во вторую очередь (с момента старта программы): %ld\n", timer.get_time_from_start()[i][1]);
        fprintf(f, "Время ожидания во второй очереди: %ld\n", timer.get_waiting_times()[i][1]);

        fprintf(f, "Время начала работы второго контейнера (с момента старта программы): %ld\n", timer.get_time_from_start()[i][2]);
        fprintf(f, "Время работы второго контейнера: %ld\n", timer.get_working_times()[i][1]);

        fprintf(f, "Время помещения в третью очередь (с момента старта программы): %ld\n", timer.get_time_from_start()[i][3]);
        fprintf(f, "Время ожидания в третьей очереди: %ld\n", timer.get_waiting_times()[i][2]);

        fprintf(f, "Время начала работы третьего контейнера (с момента старта программы): %ld\n", timer.get_time_from_start()[i][4]);
        fprintf(f, "Время работы третьего контейнера: %ld\n", timer.get_working_times()[i][2]);

        fprintf(f, "Время начала работы третьего контейнера (с момента старта программы): %ld\n", timer.get_time_from_start()[i][5]);

        fprintf(f, "Минимальное время ожидания: %ld\n", timer.get_min_time()[i]);
        fprintf(f, "Максимальное время ожидания: %ld\n", timer.get_max_time()[i]);
        fprintf(f, "Среднее время ожидания: %ld\n", timer.get_avg_time()[i]);
        fprintf(f, "Время выполнения: %ld\n", timer.get_proc_time()[i]);
        fprintf(f, "----------------------------------------------------------------------------\n");
    }

    fprintf(f, "Общее время работы системы: %ld\n", time);
    fclose(f);

    cout << "Результаты замеров времени записаны в файл журналирования" << endl;
}

int parallel()
{
    srand(time(nullptr));
    cout << "Введите размер очереди (количество строк): ";
    cin >> n;
    if (n <= 0)
    {
        cout << "Некорректный ввод";
        return INPUT_FAIL;
    }

    objvec.resize(n);
    timer.set_size();

    for (int i = 0; i < n; i++)
    {
        string s = generate(SIZE);
        objvec[i] = s;
    }

    start_t = clock();

    thread t1(first_conv);
    thread t2(second_conv);
    thread t3(third_conv);

    for (int i = 0; i < n; i++)
    {
        m1.lock();
        queue1.push(Object(objvec[i], i, clock()));
        m1.unlock();
    }

    t1.join();
    t2.join();
    t3.join();

    create_log(clock() - start_t, "paral.txt");

    //for (size_t i = 0; i < res.size(); ++i)
        //cout << objvec[i] << " --> " << res[i] << endl;

    return SUCCESS;
}

void first_line()
{
    int num = 0;
    while (true)
    {
        if (num == n)
            break;
        if (queue1.empty())
            continue;
        string cur_str = queue1.front().str;
        int cur_task_num = queue1.front().task_num;
        timer.add_time_from_start(clock() - start_t, cur_task_num);
        timer.add_time(1, clock() - queue1.front().time, queue1.front().task_num);
        queue1.pop();

        clock_t cur_time = clock();
        string new_str = caesar(cur_str);
        timer.add_time_from_start(clock() - start_t, cur_task_num);
        timer.add_time(0, clock() - cur_time, cur_task_num);

        queue2.push(Object(new_str, cur_task_num, clock()));
        num++;
    }
}

void second_line()
{
    int num = 0;
    while (true)
    {
        if (num == n)
            break;
        if (queue2.empty())
            continue;
        string cur_str = queue2.front().str;
        int cur_task_num = queue2.front().task_num;
        timer.add_time_from_start(clock() - start_t, cur_task_num);
        timer.add_time(1, clock() - queue2.front().time, queue2.front().task_num);
        queue2.pop();

        clock_t cur_time = clock();
        string new_str = upper_lower(cur_str);
        timer.add_time_from_start(clock() - start_t, cur_task_num);
        timer.add_time(0, clock() - cur_time, cur_task_num);

        queue3.push(Object(new_str, cur_task_num, clock()));
        num++;
    }
}

void third_line()
{
    int num = 0;
    while (true)
    {
        if (num == n)
            break;
        if (queue3.empty())
            continue;
        string cur_str = queue3.front().str;
        int cur_task_num = queue3.front().task_num;
        timer.add_time_from_start(clock() - start_t, cur_task_num);
        timer.add_time(1, clock() - queue3.front().time, queue3.front().task_num);
        queue3.pop();

        clock_t cur_time = clock();
        string new_str = shift_str(cur_str);
        timer.add_time_from_start(clock() - start_t, cur_task_num);
        timer.add_time(0, clock() - cur_time, cur_task_num);

        res.push_back(new_str);
        num++;
    }
}

int synch()
{
    srand(time(nullptr));
    cout << "Введите размер очереди (количество строк): ";
    cin >> n;
    if (n <= 0)
    {
        cout << "Некорректный ввод";
        return INPUT_FAIL;
    }

    objvec.resize(n);
    timer.set_size();

    for (int i = 0; i < n; i++)
    {
        string s = generate(SIZE);
        objvec[i] = s;
    }

    start_t = clock();

    for (int i = 0; i < n; i++)
        queue1.push(Object(objvec[i], i, clock()));
    first_line();
    if (!queue2.empty())
        second_line();
    if(!queue3.empty())
        third_line();

    create_log(clock() - start_t, "synch.txt");

    //for (size_t i = 0; i < res.size(); ++i)
        //cout << objvec[i] << " --> " << res[i] << endl;

    return SUCCESS;
}

int main()
{
    int choice = -1;
    while (choice)
    {
        cout << "Меню:" << endl;
        cout << "1. Решение задачи на параллельных конвейерах" << endl;
        cout << "2. Решение задачи на синхронных конвейерах" << endl;
        cout << "0. Выход\n" << endl;
        cout << "Выберите пункт меню: ";
        cin >> choice;

        if (choice == 1)
            parallel();
        else if (choice == 2)
            synch();
    }

    return SUCCESS;
}
