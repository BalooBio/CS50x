##Examples of using dot notation
text = input("Enter a string")
text = text.strip()
text = text.capitalize()
print(text)

## In python, stings (str) are objects
## doc.python.org has list of all methods related to objects

## form problemset 3, we made a stuct called candidate

LOOPS
##
for c in text:
    print(c)

text.split() # separates words in a list for each character

## so in the following code, words is not a string, its a list
words = text.split()
for word in words:
    print(word)

## Print alwasy adds a new line unless you tell it not to:
print(word, end =" ")

for word in text.split():
    for c in word:
        print(c)
#^this would print every character, minus the spaces

## when dealing with stings
[x:y]
## x is start
## y is end
## So the following would print "great green room"
text = "In the great green room
    for word in text.split() [2:]:
    print(word)

## and the following would print the whoe string
text = "In the great green room
words = text.split()
print(words[0:])

DICTIONARIES

book = dict()
book["title"] = "Courdurouy"
book["author"] = "Don Freeman"]
print(book["title"])

______________

books = [] ## dictionaries have square braces

for i in range(4):
    book = dict()
    book["author"] = input("Enter an author:")
    book["title"] = input("Enter a title:")
    books.append(book)

for book in books:
    print (f"{book["author"]} wrote {book["title"]}."
### why did the insturctor make a list of dictionaries, rather than one?
### csv files (comma separated values)
CSV MODULE
________
import csv

csv.DictReader(...)
csv.reader(..)

## or

from csv import DictReader

 READING and WRITING fro FILES

with open(FILENAME) ase file:
    text = file.read()
## for csv
with open(FILENAME) ase file:
    file_reader = csv.DictReader(file) ## will read every row of the file as a dictionary
    for row in file_reader:
        ...
______ Example, reads.py _________________

import csv

books = []

with open("books.csv") as file:
    reader = csv.DictReader(file) ## reader is an iterable
    for row in reader:
        books.append(row)

## why do you use with ?
## bc with handles some things for you, like closing the file
## like if you did  file = open("books.csv")

