from algorithms import *
from measure_time import *

def get_time():
    n = 100
    #for i in range(2, 12, 2):
        #print("Длина строки: ", i)
        #print("Рекурсивный алгоритм Левенштейна: ", "{0:.6f}".format(measure_time(lev_recursion, n, i)))
        #print("Рекурсивный алгоритм Левенштейна с кэшем: ", "{0:.6f}".format(measure_time(rec_lev_cache, n, i)))
        #print("Рекурсивный алгоритм Дамерау-Левенштейна: ", "{0:.6f}".format(measure_time(lev_damerau_recursion, n, i)))
        #print("Нерекурсивный алгоритм Дамерау-Левенштейна (с матрицей): ", "{0:.6f}".format(measure_time(lev_damerau_matrix, n, i)))
    for i in range(60, 500, 50):
        print("Длина строки: ", i)
        #print("Рекурсивный алгоритм Левенштейна: ", "{0:.6f}".format(measure_time(lev_recursion, n, i)))
        #print("Рекурсивный алгоритм Левенштейна с кэшем: ", "{0:.6f}".format(measure_time(rec_lev_cache, n, i)))
        #print("Рекурсивный алгоритм Дамерау-Левенштейна: ", "{0:.6f}".format(measure_time(lev_damerau_recursion, n, i)))
        print("Нерекурсивный алгоритм Дамерау-Левенштейна (с матрицей): ", "{0:.6f}".format(measure_time(lev_damerau_matrix, n, i)))
