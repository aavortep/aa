import threading as th
from math import *

def mult_matrs(row, matr, cols_n):
    res = [0 for i in range(len(row))]
    for i in range(cols_n):
        for j in range(len(row)):
            res[j] += row[j] * matr[j][i]
    return res

def rot(points, fi):
    res = [[0, 0] for x in range(len(points))]
    for i in range(len(points)):
        res[i][0] = points[i][0]
        res[i][1] = points[i][1]

    rad = fi * pi / 180
    rot_matr = [[cos(rad), sin(rad)], [-sin(rad), cos(rad)]]
    
    for i in range(len(res)):
        res[i] = mult_matrs(points[i], rot_matr, 2)
    return res

def rot_part(part, rot_matr, wait_ev, set_ev):
    wait_ev.wait()
    wait_ev.clear()
    for i in range(len(part)):
        part[i] = mult_matrs(part[i], rot_matr, 2)
    set_ev.set()
    return part

def rot_paral(points, fi, thr_n):
    res = [[0, 0] for x in range(len(points))]
    for i in range(len(points)):
        res[i][0] = points[i][0]
        res[i][1] = points[i][1]

    rad = fi * pi / 180
    rot_matr = [[cos(rad), sin(rad)], [-sin(rad), cos(rad)]]

    ev = [th.Event() for i in range(thr_n)]
    ths = [th.Thread(target=rot_part, args=(res[(i * len(res) // thr_n) : ((i + 1) * len(res) // thr_n)],\
                                            rot_matr, ev[i], ev[i + 1])) for i in range(thr_n - 1)]
    ths.append(th.Thread(target=rot_part, args=(res[((thr_n - 1) * len(res) // thr_n) : ], rot_matr, ev[thr_n - 1], ev[0])))

    for i in range(thr_n):
        ths[i].start()

    ev[0].set()

    for i in range(thr_n):
        ths[i].join()
    return res
