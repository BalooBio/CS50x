from cs50 import get_int

number = get_int("Number: ")

# Function that takes a number and returns true if it is a valid credit card number, else false
# Preformed using Luhn's algorithm


def checksum(x):
    sum = 0
    n = 0
    # Modulo of 10 will give the last digit of a number
    # Starting with the last digit of the number, begin doing the following:
    # multiply every other digit by 2 and add product to the sum variable
    # add all other digits (those not multiplied by 2) to the sum variable
    while x > 0:
        if (n + 1) % 2 != 0:
            sum += (x % 10)
        else:
            if ((x % 10) * 2) > 9:
                sum += (((x % 10) * 2) % 10) + 1
            else:
                sum += (x % 10) * 2
        x = x // 10
        n += 1

    if (sum % 10) == 0:
        return True, n
    else:
        return False, n


n = checksum(number)

if n[0] == True and n[1] == 15 and (number//(10**(n[1]-2))) in {34, 37}:
    print("AMEX")

elif n[0] == True and n[1] in {13, 16} and (number//(10**(n[1]-1))) % 10 == 4:
    print("VISA")

elif n[0] == True and n[1] == 16 and (number//(10**(n[1]-2))) in range(51, 56):
    print("MASTERCARD")

else:
    print("INVALID")
