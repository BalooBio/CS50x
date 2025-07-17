from cs50 import get_int

height = get_int("Height: ")

while height < 1 or height > 8:
    print("Height must an integer between 1 and 8")
    height = get_int("Height: ")


blanks = height - 1

for number in range(height):
    # Print blank space
    print(" " * blanks + "#" * (number + 1) + "  " + "#" * (number + 1))
    blanks -= 1
