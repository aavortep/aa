from algorithms import *

def by_hand():
    n = int(input("Длина массива: "))
    arr = [0 for x in range(n)]
    print("Массив чисел:")
    for i in range(n):
        arr[i] = float(input())
    
    print("")

    print("Сортировка пузырьком: ", bubble_sort(arr, n))
    print("Сортировка вставками: ", insert_sort(arr, n))
    print("Сортировка выбором: ", select_sort(arr, n))

    print("")
