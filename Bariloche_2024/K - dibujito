matrix = []


def print_m():
    for i in range(len(matrix)):
        for j in range(len(matrix[0])):
            print(matrix[i][j], end=" ")
        print()
    print("---------------------------------")


def check_T(y, x):
    if (
        y - 4 >= 0
        and x - 2 >= 0  # Verifica límites
        and matrix[y][x] == 1
        and matrix[y][x - 1] == 1
        and matrix[y][x - 2] == 1
        and matrix[y - 1][x - 1] == 1
        and matrix[y - 2][x - 1] == 1
        and matrix[y - 3][x - 1] == 1
        and matrix[y - 4][x - 1] == 1
    ):
        return True
    return False


def check_P(y, x):
    if (
        y - 4 >= 0
        and x + 2 < m
        and matrix[y - 1][x] == 1
        and matrix[y - 2][x] == 1
        and matrix[y - 3][x] == 1
        and matrix[y - 4][x] == 1
        and matrix[y - 4][x + 1] == 1
        and matrix[y - 4][x + 2] == 1
        and matrix[y - 3][x + 2] == 1
        and matrix[y - 2][x + 2] == 1
        and matrix[y - 2][x + 1] == 1
        and matrix[y - 3][x + 1] == 0
    ):
        return True
    return False


def check_A(y, x):
    if (
        y - 4 >= 0
        and x - 2 >= 0
        and matrix[y - 1][x] == 1
        and matrix[y - 2][x] == 1
        and matrix[y - 3][x] == 1
        and matrix[y - 4][x] == 1
        and matrix[y - 0][x - 2] == 1
        and matrix[y - 1][x - 2] == 1
        and matrix[y - 2][x - 2] == 1
        and matrix[y - 3][x - 2] == 1
        and matrix[y - 4][x - 2] == 1
        and matrix[y - 2][x - 1] == 1
        and matrix[y - 3][x - 1] == 0
        and matrix[y - 4][x - 1] == 1
    ):
        return True
    return False


def delete_T(y, x):
    for i in range(5):
        matrix[y - i][x] = 0
    for i in range(3):
        matrix[y - 4][x - 1 + i] = 0


def delete_P(y, x):
    for i in range(5):
        matrix[y - i][x] = 0
    matrix[y - 4][x + 1] = 0
    matrix[y - 4][x + 2] = 0
    matrix[y - 3][x + 2] = 0
    matrix[y - 2][x + 2] = 0
    matrix[y - 2][x + 1] = 0


def delete_A(y, x):
    for i in range(5):
        matrix[y - i][x] = 0
        matrix[y - i][x - 2] = 0
    matrix[y - 2][x - 1] = 0
    matrix[y - 4][x - 1] = 0


def count_letters(n, m):
    count_T = 0
    count_A = 0
    count_P = 0
    for y in range(n - 1, 3, -1):
        for x in range(m - 1, -1, -1):
            if matrix[y][x] == 1:
                if check_P(y, x):
                    count_P += 1
                    delete_P(y, x)
                elif check_A(y, x):
                    count_A += 1
                    delete_A(y, x)
                else:
                    count_T += 1
                    delete_T(y, x)
    return count_T, count_A, count_P


n, m = map(int, input().split())
for _ in range(n):
    line = input().strip()
    matrix.append([1 if char == "#" else 0 for char in line])

result_T, result_A, result_P = count_letters(n, m)
print(result_T, result_A, result_P)
