#include <iostream>

void quick(int *mas, int size)
{
    int i = 0;  // (1)
    int j = size - 1;  // (2)
    int mid = mas[size / 2];  // (3)
    do  // (4)
    {
        while (mas[i] < mid)  // (5)
            i++;  // (6)
        while (mas[j] > mid)  // (7)
            j--;  // (8)
        if (i <= j)  // (9)
        {
            int tmp = mas[i];  // (10)
            mas[i] = mas[j];  // (11)
            mas[j] = tmp;  // (12)
            i++;  // (13)
            j--;  // (14)
        }
    }
    while (i <= j);  // (4)
    if (j > 0)  // (15)
        quick(mas, j + 1);  // (16)
    if (i < size)  // (17)
        quick(&mas[i], size - i);  // (18)
}

int main()
{
    int arr[5] = { 54, 26, 93, 17, 77 };
    quick(arr, 5);
    for (int i = 0; i < 5; ++i)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
    return 0;
}