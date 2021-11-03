from algorithms import *
import string
import random
from time import process_time

def generate_str(length):
    let = string.ascii_lowercase
    s = ''.join(random.choice(let) for i in range(length))
    return s

def measure_time(function, n, length):
    t1 = process_time() 
    for i in range(n):
        str1 = generate_str(length)
        str2 = generate_str(length)
        function(str1, str2, len(str1), len(str2))
    t2 = process_time() 
    return (t2 - t1) / n
