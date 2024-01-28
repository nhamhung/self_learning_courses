from math import sqrt


def improve(update, close, guess=1):
    while not close(guess):
        guess = update(guess)

    return guess


def square_close_to_successor(guess):
    return approx_eq(guess * guess, guess + 1)


def approx_eq(x, y, tolerance=1e-15):
    return abs(x - y) < tolerance


def golden_update(guess):
    return 1/guess + 1


# 2 special properties of phi
# Can be computed by repeatedly sum inverse of any positive number with 1 and Is 1 less than its square
phi = 1/2 + sqrt(5)/2


def improve_test():
    approx_phi = improve(golden_update, square_close_to_successor)
    assert approx_eq(phi, approx_phi), 'phi differs from its approximation'


improve_test()
