from algorithms import *
import random
from time import process_time

def generate_pts(num):
    pts = [[0, 0] for x in range(num)]
    for i in range(num):
        pts[i][0] = random.randint(-100, 100)
        pts[i][1] = random.randint(-100, 100)
    return pts

def measure_time(function, n, pts_n = 1000, thr_n = 4):
    fi = 45
    t1 = process_time()
    for i in range(n):
        pts = generate_pts(pts_n)
        if function == rot:
            function(pts, fi)
        else:
            function(pts, fi, thr_n)
    t2 = process_time() 
    return (t2 - t1) / n
