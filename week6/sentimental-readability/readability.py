from cs50 import get_string

text = get_string("Text: ")

# Set baseline values for counting number of letters, words, and sentences in text
letters = 0
words = 1
sentences = 0

# Get number of letters, words, and sentences
for char in text:

    if char.isalpha():
        letters += 1

    elif char.isspace():
        words += 1

    elif char == "." or char == "!" or char == "?":
        sentences += 1

# Avg number of letters per 100 words, L
L = (letters / words) * 100

# Average number of sentences per 100 words, S
S = (sentences / words) * 100

# Calculate Coleman-Liau index
index = 0.0588 * L - 0.296 * S - 15.8

# Check if index is lower than 1 or above 16, and respond as indicated in instructions
# If not, print the grade level
if index < 1:
    print("Before Grade 1")

elif index >= 16:
    print("Grade 16+")

else:
    print(f"Grade {round(index)}")
