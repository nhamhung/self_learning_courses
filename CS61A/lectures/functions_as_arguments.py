def sum_of_terms(n, term):
    total = 0

    for i in range(1, n+1):
        total += term(i)

    return total


def cube(x):
    return x*x*x


def sum_cubes(n):
    return sum_of_terms(n, cube)


assert 36 == sum_cubes(3)
