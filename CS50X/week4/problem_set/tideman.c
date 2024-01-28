#include "../../my_library.h"
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

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

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
    // candidates[]{"Alice", "Bob", "Charlie"}
    // ranks[]{2, 0, 1}
    for (int candidate = 0; candidate < candidate_count; candidate++)
    {
        if (strcmp(candidates[candidate], name) == 0)
        {
            ranks[rank] = candidate;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // How many voters prefer candidate 0 over 1
    // For each distinct pair of indexes (i, j) in ranks, increase preferences[ranks[i]][ranks[j]] since
    // ranks[i] is preferred over ranks[j]
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            int winner = ranks[i];
            int loser = ranks[j];
            preferences[winner][loser] += 1;
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    int num_pairs = 0;

    for (int candidate_1 = 0; candidate_1 < candidate_count - 1; candidate_1++)
    {
        for (int candidate_2 = candidate_1 + 1; candidate_2 < candidate_count; candidate_2++)
        {
            if (preferences[candidate_1][candidate_2] > preferences[candidate_2][candidate_1])
            {
                pairs[num_pairs] = (pair){candidate_1, candidate_2};
                num_pairs += 1;
            }
            else if (preferences[candidate_2][candidate_1] > preferences[candidate_1][candidate_2])
            {
                pairs[num_pairs] = (pair){candidate_2, candidate_1};
                num_pairs += 1;
            }
        }
    }

    pair_count = num_pairs;

    return;
}

void swap(pair *xp, pair *yp)
{
    pair temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    bool swapped;
    for (int i = 0; i < pair_count; i++)
    {
        swapped = false;
        for (int j = 0; j < pair_count - i - 1; j++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] < preferences[pairs[j + 1].winner][pairs[j + 1].loser])
            {
                swap(&pairs[j], &pairs[j + 1]);
                swapped = true;
            }
        }

        if (swapped == false)
        {
            break;
        }
    }
    return;
}

bool has_cycle(int winner, int loser)
{
    if (winner == loser)
    {
        return true;
    }

    for (int candidate = 0; candidate < candidate_count; candidate++)
    {
        if (locked[loser][candidate])
        {
            if (has_cycle(winner, candidate))
            {
                return true;
            }
        }
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
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    for (int col = 0; col < candidate_count; col++)
    {
        bool isLoser = false;

        for (int row = 0; row < candidate_count; row++)
        {
            if (locked[row][col])
            {
                isLoser = true;
                break;
            }
        }

        if (!isLoser)
        {
            printf("%s\n", candidates[col]);
            break;
        }
    }

    return;
}