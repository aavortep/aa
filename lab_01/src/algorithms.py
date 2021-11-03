def lev_recursion(str1, str2, len1, len2):
    if (len1 == len2) and len1 == 0:
        return 0
    elif len1 == 0:
        return len2
    elif len2 == 0:
        return len1
    else:
        flag = bool(not (str1[len1 - 1] == str2[len2 - 1]))
        return min(min(lev_recursion(str1, str2, len1 - 1, len2) + 1,
                       lev_recursion(str1, str2, len1, len2 - 1) + 1),
                   lev_recursion(str1, str2, len1 - 1, len2 - 1) + flag)

def lev_cache(str1, str2, len1, len2, mtx):
    if not mtx[len1][len2] == 0:
        return mtx[len1][len2]
    elif (len1 == len2) and (len1 == 0):
        mtx[len1][len2] = 0
    elif len1 == 0:
        mtx[len1][len2] = len2
    elif len2 == 0:
        mtx[len1][len2] = len1
    else:
        flag = bool(not(str1[len1 - 1] == str2[len2 - 1]))
        mtx[len1][len2] = min(min(lev_cache(str1, str2, len1 - 1, len2, mtx) + 1,
                                   lev_cache(str1, str2, len1, len2 - 1, mtx) + 1),
                               lev_cache(str1, str2,  len1 - 1, len2 - 1, mtx) + flag)
    return mtx[len1][len2]

def rec_lev_cache(str1, str2, len1, len2):
    mtx = [[0 for x in range(len2 + 1)] for y in range(len1 + 1)]
    return (lev_cache(str1, str2, len1, len2, mtx), mtx)

def lev_damerau_recursion(str1, str2, len1, len2):
    if (len1 == len2) and len1 == 0:
        return 0
    elif len1 == 0:
        return len2
    elif len2 == 0:
        return len1
    else:
        flag = bool(not(str1[len1 - 1] == str2[len2 - 1]))
        res = min(lev_damerau_recursion(str1, str2, len1 - 1, len2) + 1,
                  lev_damerau_recursion(str1, str2, len1, len2 - 1) + 1,
                  lev_damerau_recursion(str1, str2, len1 - 1, len2 - 1) + flag)
        if (len1 >= 2 and len2 >= 2 and str1[len1 - 1] == str2[len2 - 2] and str1[len1 - 2] == str2[len2 - 1]):
            res = min(res, lev_damerau_recursion(str1, str2, len1 - 2, len2 - 2) + 1)
        return res 

def lev_damerau_matrix(str1, str2, len1, len2):
    mtx = [[0 for x in range(len2 + 1)] for y in range(len1 + 1)]
    for i in range(len2 + 1):
        mtx[0][i] = i
    for i in range(1, len1 + 1):
        mtx[i][0] = i
    for i in range(1, len1 + 1):
        for j in range(1, len2 + 1):
            add, delete, change = mtx[i - 1][j] + 1, mtx[i][j - 1] + 1, mtx[i - 1][j - 1]
            if str2[j - 1] != str1[i - 1]:
                change += 1
            mtx[i][j] = min(add, delete, change)
            if ((i > 1 and j > 1) and str1[i - 1] == str2[j - 2] and str1[i - 2] == str2[j - 1]):
                mtx[i][j] = min(mtx[i][j], mtx[i - 2][j - 2] + 1)
    return (mtx[len1][len2], mtx)
