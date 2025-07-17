from cs50 import get_string

text = get_string("Text: ")

n=0
for char in text:
    if char.isalpha():
        n += 1
print(n)
