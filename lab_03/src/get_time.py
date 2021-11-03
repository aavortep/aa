from algorithms import *
from measure_time import *

def get_time():
    n = 100
    print("Лучший случай:")
    print("")
    for i in range(100, 2200, 200):
        print("Длина массива: ", i)
        arr = [j for j in range(i)]
        t1 = process_time()
        for j in range(n):
            bubble_sort(arr, i)
        t2 = process_time() 
        t = (t2 - t1) / n
        print("Сортировка пузырьком: ", "{0:.6f}".format(t))
        t1 = process_time()
        for j in range(n):
            insert_sort(arr, i)
        t2 = process_time() 
        t = (t2 - t1) / n
        print("Сортировка вставками: ", "{0:.6f}".format(t))
        t1 = process_time()
        for j in range(n):
            select_sort(arr, i)
        t2 = process_time() 
        t = (t2 - t1) / n
        print("Сортировка выбором: ", "{0:.6f}".format(t))
        print("")
    
    print("Худший случай:")
    print("")
    for i in range(100, 2200, 200):
        print("Длина массива: ", i)
        arr = [i - j for j in range(i)]
        t1 = process_time()
        for j in range(n):
            bubble_sort(arr, i)
        t2 = process_time() 
        t = (t2 - t1) / n
        print("Сортировка пузырьком: ", "{0:.6f}".format(t))
        t1 = process_time()
        for j in range(n):
            insert_sort(arr, i)
        t2 = process_time() 
        t = (t2 - t1) / n
        print("Сортировка вставками: ", "{0:.6f}".format(t))
        t1 = process_time()
        for j in range(n):
            select_sort(arr, i)
        t2 = process_time() 
        t = (t2 - t1) / n
        print("Сортировка выбором: ", "{0:.6f}".format(t))
        print("")

    print("Произвольный случай:")
    print("")
    for i in range(100, 2200, 200):
        print("Длина массива: ", i)
        print("Сортировка пузырьком: ", "{0:.6f}".format(measure_time(bubble_sort, n, i)))
        print("Сортировка вставками: ", "{0:.6f}".format(measure_time(insert_sort, n, i)))
        print("Сортировка выбором: ", "{0:.6f}".format(measure_time(select_sort, n, i)))
        print("")
