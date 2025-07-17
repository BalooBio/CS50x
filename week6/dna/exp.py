import csv
import sys

data = []

#with open("databases/small.csv") as file:
#    text = file.read()
#    print(text)

with open("databases/small.csv") as file:
    reader = csv.DictReader(file)
    #loop over reader, which gives every row as a dictionary
    for row in reader:
        # append row to list "data"
        data.append(row)

for row in data:
    print(row)


dna = []

with open("sequences/1.txt") as file:
    dna = file.read()

print(len(dna[0]))
print(len(data[0]))

for key in data[0]:
    print(key)

