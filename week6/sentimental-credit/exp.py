from cs50 import get_int

number = get_int("Number: ")

def checksum(x):
    n = 0
    while x > 0:
        x = x // 10
        n += 1
    return n;

n = checksum(number)
print(n)
print((number//(10**(n-1))) % 10)
