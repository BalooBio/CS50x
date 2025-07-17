#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;
int locked_count;
int locked_array[MAX];

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
bool is_cycle(int winner, int looser);
void lock_pairs(void);
bool is_source(int i);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        /// bc argv[0] is the call to tideman
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs -- make all locked pairs false (what were they before?)
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes from each voter
    for (int i = 0; i < voter_count; i++)
    {
        // instantiate an array, ranks[], where ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);
            // vote function used to check if name given is in candidate list, and if it is, add the candidates indext to the respective position in the ranks array
            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }
        record_preferences(ranks);
        printf("\n");
    }
    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update the preferences array given the voter's ranks array
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = candidate_count - 1; j > i; j--)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                //unsure why I had to make a new pair this way
                pair new_pair = {i, j};
                pairs[pair_count] = new_pair;
                pair_count++;

            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    pair temp_pair;
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = pair_count - 1; j > i; j--)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] > preferences[pairs[i].winner][pairs[i].loser])
            {

                temp_pair = pairs[j];
                pairs[j] = pairs[i];
                pairs[i] = temp_pair;
            }
        }
    }
    return;
}

bool has_cycle(int winner, int loser)
{
    if (locked[loser][winner] == true)
    {
        return true;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i] == true && has_cycle(winner, i))
        return true;
    }
    return false;

}
// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++)
    {
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;
        if (!has_cycle(winner, loser))
        {
            locked[winner][loser] = true;
            locked_array[locked_count] = i;
            locked_count ++;
        }
    }
    return;
}

//determines if candidate in locked_array[i] is source by checking if that candidate is listed as the loser in any of the other locked pairs
bool is_source(int i)
{
    for (int j = 0; j < locked_count; j++)
    {
        if (locked[pairs[locked_array[j]].winner][i])
        return false;
    }
    return true;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    int source;
    for (int i = 0; i < locked_count; i++)
    {
        if (pairs[locked_array[i]].winner != source)
        {
            if (is_source(pairs[locked_array[i]].winner) == true)
            {
                source = pairs[locked_array[i]].winner;
                printf ("%s\n", candidates[pairs[locked_array[i]].winner]);
            }
        }
    }
    return;
}
