def bubble_sort(arr, n):
    res = [arr[x] for x in range(n)]
    for i in range(n):
        for j in range(n - i - 1):
            if res[j] > res[j + 1]:
                res[j], res[j + 1] = res[j + 1], res[j]
    return res

def insert_sort(arr, n):
    res = [arr[x] for x in range(n)]
    for i in range(n):
        current = res[i]
        j = i
        while (res[j - 1] > current) and (j > 0):
            res[j] = res[j - 1]
            j -= 1
        res[j] = current
    return res

def select_sort(arr, n):
    res = [arr[x] for x in range(n)]
    for i in range(n - 1):
        id_min = i
        for j in range(i + 1, n):
            if res[j] < res[id_min]:
                id_min = j
        res[i], res[id_min] = res[id_min], res[i]
    return res
