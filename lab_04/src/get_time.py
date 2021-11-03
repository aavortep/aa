from algorithms import *
from measure_time import *

def get_time():
    n = 100
    thr_n = 2
    print("Кол-во потоков для распараллеливания: ", thr_n)
    print("")
    for i in range(1000, 10001, 1000):
        print("Количество точек: ", i)
        print("Последовательный алгоритм: ", "{0:.6f}".format(measure_time(rot, n, i)))
        print("Распараллеливание: ", "{0:.6f}".format(measure_time(rot_paral, n, i, thr_n)))
        print("")

    i = 1
    points_n = 8000
    print("Кол-во точек: ", points_n)
    print("")
    while i <= 16:
        print("Количество потоков: ", i)
        print("Последовательный алгоритм: ", "{0:.6f}".format(measure_time(rot, n, points_n)))
        print("Распараллеливание: ", "{0:.6f}".format(measure_time(rot_paral, n, points_n, i)))
        print("")
        i *= 2
