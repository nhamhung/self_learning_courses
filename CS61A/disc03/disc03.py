def multiply(m, n):
    """Takes two positive integers and returns their product using recursion.
    >>> multiply(5, 3)
    15
    """
    if n == 1:
        return m

    return m + multiply(m, n - 1)


def skip_mul(n):
    """Return the product of n * (n - 2) * (n - 4) * ...

    >>> skip_mul(5) # 5 * 3 * 1
    15
    >>> skip_mul(8) # 8 * 6 * 4 * 2
    384
    """
    if n == 1 or n == 2:
        return n
    else:
        return n * skip_mul(n - 2)


def is_prime(n):
    """Returns True if n is a prime number and False otherwise.
    >>> is_prime(2)
    True
    >>> is_prime(16)
    False
    >>> is_prime(521)
    True
    """
    def is_prime_recursive(n, i):
        if i * i > n:
            return True
        else:
            # only true if False for all i
            return n % i != 0 and is_prime_recursive(n, i + 1)

    return is_prime_recursive(n, 2)


print(is_prime(16))
