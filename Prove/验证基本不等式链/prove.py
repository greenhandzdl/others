import random

n = 10000
mat = [1, n]
for __count in range(n):
    mat.append(random.randint(1, 100000))
print('算术平均数是:', 算术平均数(mat, n))

def 算术平均数(mat, n):
    res = 0
    i = 0
    for __count in range(n):
        res += mat[i]
        mat += 1
    return (res / n)
