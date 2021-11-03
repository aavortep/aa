from algorithms import *

def input_matr(rows_n, cols_n):
    matr = [[0 for x in range(cols_n)] for y in range(rows_n)]
    for i in range(rows_n):
        for j in range(cols_n):
            matr[i][j] = int(input())
    return matr

def print_matr(matr, rows_n, cols_n):
    for i in range(rows_n):
        for j in range(cols_n):
            print(matr[i][j], end = ' ')
        print("")

def by_hand():
    print("Матрица А:")
    M = int(input("Введите кол-во строк: "))
    N = int(input("Введите кол-во столбцов: "))
    print("Введите матрицу:")
    matr_a = input_matr(M, N)
    
    print("")

    print("Матрица B:")
    Q = int(input("Введите кол-во столбцов: "))
    print("Введите матрицу:")
    matr_b = input_matr(N, Q)

    print("")
    
    res = std_mult(matr_a, matr_b, M, N, Q)
    print("Обычное умножение:")
    print_matr(res, M, Q)

    res = win_mult(matr_a, matr_b, M, N, Q)
    print("Алгоритм Винограда:")
    print_matr(res, M, Q)

    res = opt_win_mult(matr_a, matr_b, M, N, Q)
    print("Улучшенный алгоритм Винограда:")
    print_matr(res, M, Q)

    print("")
