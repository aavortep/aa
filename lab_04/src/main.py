from by_hand import *
from get_time import *

choice = 1

while choice:
    print("Меню: ")
    print("1. Ручной ввод")
    print("2. Замеры процессорного времени выполнения алгоритмов")
    print("0. Выход\n")

    try:
        choice = int(input("Выберите пункт меню: "))
    except ValueError:
        print("\nНекорректный ввод!\n")
        choice = -1
        continue
    print("")

    if choice == 1:
        by_hand()
    elif choice == 2:
        get_time()
    elif choice != 0:
        print("Некорректный ввод!\n")
