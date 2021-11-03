from algorithms import *
import random
from time import process_time

def generate_matr(rows_n, cols_n):
    matr = [[0 for x in range(cols_n)] for y in range(rows_n)]
    for i in range(rows_n):
        for j in range(cols_n):
            matr[i][j] = random.randint(-100, 100)
    return matr

def measure_time(function, n, size):
    t1 = process_time() 
    for i in range(n):
        matr_a = generate_matr(size, size)
        matr_b = generate_matr(size, size)
        function(matr_a, matr_b, size, size, size)
    t2 = process_time() 
    return (t2 - t1) / n
