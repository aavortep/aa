from algorithms import *
from measure_time import *

def get_time():
    n = 100
    print("Лучший случай:")
    print("")
    for i in range(50, 300, 50):
        print("Размер матриц: " + str(i) + " x " + str(i))
        print("Обычное умножение: ", "{0:.6f}".format(measure_time(std_mult, n, i)))
        print("Алгоритм Винограда: ", "{0:.6f}".format(measure_time(win_mult, n, i)))
        print("Улучшенный алгоритм Винограда: ", "{0:.6f}".format(measure_time(opt_win_mult, n, i)))
        print("")
    print("Худший случай:")
    print("")
    for i in range(51, 300, 50):
        print("Размер матриц: " + str(i) + " x " + str(i))
        print("Обычное умножение: ", "{0:.6f}".format(measure_time(std_mult, n, i)))
        print("Алгоритм Винограда: ", "{0:.6f}".format(measure_time(win_mult, n, i)))
        print("Улучшенный алгоритм Винограда: ", "{0:.6f}".format(measure_time(opt_win_mult, n, i)))
        print("")
