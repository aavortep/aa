def std_mult(matr_a, matr_b, M, N, Q):
    res = [[0 for x in range(Q)] for y in range(M)]
    for i in range(M):
        for j in range(Q):
            for k in range(N):
                res[i][j] = res[i][j] + matr_a[i][k] * matr_b[k][j]
    return res


def precomp_rows(matr, M, N):
    mul_h = [0 for x in range(M)]
    for i in range(M):
        for j in range(0, N - 1, 2):
            mul_h[i] = mul_h[i] + matr[i][j] * matr[i][j + 1]
    return mul_h

def precomp_cols(matr, M, N):
    mul_v = [0 for y in range(N)]
    for i in range(N):
        for j in range(0, M - 1, 2):
            mul_v[i] = mul_v[i] + matr[j][i] * matr[j + 1][i]
    return mul_v

def win_mult(matr_a, matr_b, M, N, Q):
    res = [[0 for x in range(Q)] for y in range(M)]
    
    mul_h = precomp_rows(matr_a, M, N)
    mul_v = precomp_cols(matr_b, N, Q)

    for i in range(M):
        for j in range(Q):
            res[i][j] = -mul_h[i] - mul_v[j]
            for k in range(0, N - 1 , 2):
                res[i][j] = res[i][j] + (matr_a[i][k] + matr_b[k + 1][j]) * (matr_a[i][k + 1] + matr_b[k][j])
    if N % 2 != 0:
        for i in range(M):
            for j in range(Q):
                res[i][j] = res[i][j] + matr_a[i][N - 1] * matr_b[N - 1][j]
    return res


def opt_precomp_rows(matr, M, N):
    mul_h = [0 for x in range(M)]
    for i in range(M):
        for j in range(0, N - 1, 2):
            mul_h[i] += (matr[i][j] * matr[i][j + 1])
    return mul_h

def opt_precomp_cols(matr, M, N):
    mul_v = [0 for y in range(N)]
    for i in range(N):
        for j in range(0, M - 1, 2):
            mul_v[i] += (matr[j][i] * matr[j + 1][i])
    return mul_v

def opt_win_mult(matr_a, matr_b, M, N, Q):
    res = [[0 for x in range(Q)] for y in range(M)]
    
    mul_h = opt_precomp_rows(matr_a, M, N)
    mul_v = opt_precomp_cols(matr_b, N, Q)

    odd = N % 2

    for i in range(M):
        for j in range(Q):
            res[i][j] = -mul_h[i] - mul_v[j]
            for k in range(0, N - 1 , 2):
                res[i][j] += ((matr_a[i][k] + matr_b[k + 1][j]) * (matr_a[i][k + 1] + matr_b[k][j]))
            if odd:
                res[i][j] += (matr_a[i][N - 1] * matr_b[N - 1][j])
    return res
