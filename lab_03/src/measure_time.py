from algorithms import *
import random
from time import process_time

def generate_arr(size):
    arr = [0 for x in range(size)]
    for i in range(size):
        arr[i] = random.randint(-100, 100)
    return arr

def measure_time(function, n, size):
    t1 = process_time() 
    for i in range(n):
        arr = generate_arr(size)
        function(arr, size)
    t2 = process_time() 
    return (t2 - t1) / n
