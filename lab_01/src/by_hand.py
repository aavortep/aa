from algorithms import *

def by_hand():
    str1 = str(input("Первая строка: "))
    str2 = str(input("Вторая строка: "))
    len1 = len(str1)
    len2 = len(str2)
    print("")
    print("Рекурсивный алгоритм Левенштейна:", lev_recursion(str1, str2, len1, len2))
    res, mtx = rec_lev_cache(str1, str2, len1, len2)
    print("Рекурсивный алгоритм Левенштейна с кэшем:",  res)
    print("Использованная матрица:")
    for i in range(len1 + 1):
        for j in range(len2 + 1):
            print(mtx[i][j], end = ' ')
        print("")
    print("Рекурсивный алгоритм Дамерау-Левенштейна:", lev_damerau_recursion(str1, str2, len1, len2))
    res, mtx = lev_damerau_matrix(str1, str2, len1, len2)
    print("Нерекурсивный алгоритм Дамерау-Левенштейна (с матрицей):",  res)
    print("Использованная матрица:")
    for i in range(len1 + 1):
        for j in range(len2 + 1):
            print(mtx[i][j], end = ' ')
        print("")
    
