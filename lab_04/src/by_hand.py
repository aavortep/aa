from algorithms import *

def by_hand():
    n = int(input("Количество точек: "))
    points = [[0, 0] for x in range(n)]
    print("Координаты точек (в формате: x y):")
    for i in range(n):
        points[i][0], points[i][1] = map(float, input().split(' '))
    fi = float(input("Угол поворота (в градусах): "))
    
    print("")
    print("Результат поворота:")
    print("")

    res = rot(points, fi)
    print("Без распараллеливания:")
    for i in range(n):
        print(res[i])
    res = rot_paral(points, fi, 2)
    print("С распараллеливанием:")
    for i in range(n):
        print(res[i])

    print("")
