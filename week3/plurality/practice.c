
// Included for........
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Define maximum number of candidates
#define MAX 9

// Define the candidate struct having two fields, name and votes
typedef struct
{
    string name;
    int votes;
} candidate;

// Begin empty array called candidates -- Is there a reason this is done outside of main()?
// YES. It is used by multiple functions so it needs to be global
candidate candidates[MAX];

// Number of Candidates -- Is there a reason this is done outside of main()?
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage of command line arguments
    if (argc < 2)
    {
        printf("Usage: plurality[candidate....]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;

    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    // Get votes and update candidates.votes for each vote
    int voter_count = get_int("Number of voters: ");

    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check that user provided valid vote using function vote()
        if (!vote(name))
        {
            printf("Invalid vote\n");
        }
    }

    // Display winner of voting with print_winner function
}

bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            return true;
        }
    }
    return false;
}

void print_winner(void)
{
    int highest_vote = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > highest_vote)
        {
            highest_vote = candidates[i].votes;
        }
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == highest_vote)
        {
            printf("%s\n", candidates[i].name);
        }
    }
    return;
}
