Variables in Python
## Two big differences in Variables for Python compared to C
## dont need an identifier
## and in python, they are declared by initialization only. Cannot simply declare.
## C
int x = 54;
## Python
x = 54
## Also notice python statements dont need to end with semicolons! yay!
## Python has strings built in (whereas C had strings in the cs50 library)
## and Python supports single or double quotes when using strings, which is useful when your string has
## quotation marks in it. Usually, use single quotes on outside and double quotes on inside.
stringName = 'He said, "this is cs50"'

Conditionals in Python
## 'or' instead of '||'.
## end conditional with : instead of ;
if y < 43 or z == 14:
    code goes here ## no {} required!

## 'and' replaces '&&'
if y < 43 or z == 14:
    code block 1
else:
    code block 2

## 'elif' instead of 'else if'
if x ==50:
    code block 1
elif x == 51:
    code block 2

## Still have the terinary operator (?:) but its much easier to follow in python
## and True and Fals are capitalized
## and indentation is extreamly important
## use input instead of get_char, get_int etc.. Although we do have some of those written for use in python specifically for this course.
## C
char var = get_char();
bool alphabetic = isalpha(var) ? true : false;

## Python
letters_only = True if input().isalpha() else False


LOOPS
## 'do while loops" technically dont use the word 'do'
## no more ++
counter = 0
while counter < 100:
    print (counter)
    counter += 1
## for loops are different, but probably for the better
## in C
for(int x = 0; x < 100; x++)
{
    printf("%i\n", x)
}

## in Pythion
## range(x) gives you a list of numbers from 0 to x-1
for x in range(100):
    print(x)
## can also count by 2's by setting a start point, and end point, and how often we want to skip
for x in range(0, 100, 2):
    print(x)


ARRAYS (Lists in Python)
## not fixed in size
nums = []
or
nums = list()
nums = [1, 2, 3, 4]
nums.append(5)
## does the same thing as
nums.insert(4, 5)
## which inserts 5 into the 4 position
## this also does the same thing
nums[len(nums):] = [5]
## this says the nums list from this position len(nums) forward, gets this ([5]) assigned to it

##List comprehension
##using a for loop to generate a list for me
nums = [x for x in range(500)]



TUPLE
## an ordered, immutable sets of data
## fast to navigate and great for associating collecitons of data
## here is a list of tuples
presidents = [
    ("George Washington", 1789),
    ("John Adams", 1797),
    ("Thomas Jefferson", 1801),
    ("James Madison", 1809)
]

## How to iterate over this list
## Using the .format method
for prez, year in presidents:
    print("In {1}, {0} took office".format(prez, year))

DICTIONARIES
## allows us to associate keys with indexes (or values)
## Example
## : used to separate keys from values
pizzas = {
    "cheese": 9,
    "pepperoni": 10,
    "vegetable": 11,
    "buffalo chicken": 12
}

## Changing a vlaue

pizzas["cheese"] = 8

if pizza["vegetable"] < 12:
    order pizza....

## adding new key value pair
pizzas["sausage"] = 12

### But how do you iterate over a dictionary if the keys arent always integers??
## this can be done thanks to the flexability of the for loop
for pie in pizzas:
    print(pie)

## to iterate over the values in a fictionary, you have to tansform it to a list using the .items method
## When you do this, for some reason (BUT WHYYYYY), you arent guaranteed that the list will maintain its order
for pie, price in pizzas.items:
    print (price)

## and if you want to iterate over both
for pie, price in pizzas.items();
    print("A whole {} pizza costs ${}".format(pie, price))

# Why do you have to make a dictionary into a list in order to iterate over values?


FUNCTIONS
## introduced using def, do not have to speficy input or output.

## if you want to define a main function (you dont have to) you must have the following at the very end of your code
## dont neccessarily have to use if you write your code in order

if __name__ == "__main__":
    main()

## Defining funcitons

def square(x):
    result = 0
    for i in range(0, x):
        result += x
    return result

OBJECTS
## C has structures, which are kind of like objects. They have a number of feilds which would be considered properties
## in an object oriented language like python. But the feilds cannot stand on their own.

## In C, objects have properties (kinda like fields) and they have methods, which are funcitons specific for that object. Methods
## do not mean anythign outside of their respoective objects. So proerties and methods dont stand on their own.

## So we dont pass objects into a function, we call methods instead
object.method()

CLASS
## Objects are defined using the class keyword. They require and initialization funciton, known as a constructor, which sets the
## starting values of the propertiens for that object
## In defining each method for an object, self should eb the first parameter, which stipulates on what object the method is called.

IMPORTING MODULE instead of #Inclue

import cs50
cs50.get_int()

## you can type python in the command line and use python in your interpreter if youd like



