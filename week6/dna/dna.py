import csv
from sys import argv


def main():

    # TODO: Check for command-line usage
    if len(argv) != 3:
        print("Must input two files")
        return

    # TODO: Read database file into a variable

    data = []  # Set variable as list

    with open(argv[1]) as file:  # Read each row of the csv file into the list
        reader = csv.DictReader(file)
        for row in reader:
            data.append(row)

    # TODO: Read DNA sequence file into a variable

    dna = []

    with open(argv[2]) as file:
        dna = file.read()

    # TODO: Find longest match of each STR in DNA sequence

    matches = {}

    for key in data[0]:
        matches[key] = longest_match(dna, key)

    # TODO: Check database for matching profiles
    suspect = "No match"
    counter = 1

    for i in range(len(data)):
        for k in matches:
            if str(matches[k]) == data[i][k]:
                counter += 1

        if counter == len(data[0]):
            suspect = data[i]["name"]
            break

        else:
            counter = 1

    print(suspect)

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
