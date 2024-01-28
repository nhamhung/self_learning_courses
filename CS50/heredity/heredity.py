import csv
import itertools
import sys

PROBS = {

    # Unconditional probabilities for having gene
    "gene": {
        2: 0.01,
        1: 0.03,
        0: 0.96
    },

    "trait": {

        # Probability of trait given two copies of gene
        2: {
            True: 0.65,
            False: 0.35
        },

        # Probability of trait given one copy of gene
        1: {
            True: 0.56,
            False: 0.44
        },

        # Probability of trait given no gene
        0: {
            True: 0.01,
            False: 0.99
        }
    },

    "pass_down": {
        # Probability of passing down 0 or 1 gene given parent's gene_count
        0: {
            0: 0.99,
            1: 0.01,
        },
        1: {
            0: 0.5,
            1: 0.5,
        },
        2: {
            0: 0.01,
            1: 0.99,
        }
    },

    # Mutation probability
    "mutation": 0.01
}


def main():

    # Check for proper usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python heredity.py data.csv")
    people = load_data(sys.argv[1])

    # Keep track of gene and trait probabilities for each person
    probabilities = {
        person: {
            "gene": {
                2: 0,
                1: 0,
                0: 0
            },
            "trait": {
                True: 0,
                False: 0
            }
        }
        for person in people
    }

    # Loop over all sets of people who might have the trait
    names = set(people)
    for have_trait in powerset(names):

        # Check if current set of people violates known information
        fails_evidence = any(
            (people[person]["trait"] is not None and
             people[person]["trait"] != (person in have_trait))
            for person in names
        )
        if fails_evidence:
            continue

        # Loop over all sets of people who might have the gene
        for one_gene in powerset(names):
            for two_genes in powerset(names - one_gene):

                # Update probabilities with new joint probability
                p = joint_probability(people, one_gene, two_genes, have_trait)
                update(probabilities, one_gene, two_genes, have_trait, p)

    # Ensure probabilities sum to 1
    normalize(probabilities)

    # Print results
    for person in people:
        print(f"{person}:")
        for field in probabilities[person]:
            print(f"  {field.capitalize()}:")
            for value in probabilities[person][field]:
                p = probabilities[person][field][value]
                print(f"    {value}: {p:.4f}")


def load_data(filename):
    """
    Load gene and trait data from a file into a dictionary.
    File assumed to be a CSV containing fields name, mother, father, trait.
    mother, father must both be blank, or both be valid names in the CSV.
    trait should be 0 or 1 if trait is known, blank otherwise.
    """
    data = dict()
    with open(filename) as f:
        reader = csv.DictReader(f)
        for row in reader:
            name = row["name"]
            data[name] = {
                "name": name,
                "mother": row["mother"] or None,
                "father": row["father"] or None,
                "trait": (True if row["trait"] == "1" else
                          False if row["trait"] == "0" else None)
            }
    return data


def powerset(s):
    """
    Return a list of all possible subsets of set s.
    """
    s = list(s)
    return [
        set(s) for s in itertools.chain.from_iterable(
            itertools.combinations(s, r) for r in range(len(s) + 1)
        )
    ]


def joint_probability(people, one_gene, two_genes, have_trait):
    """
    Compute and return a joint probability.

    The probability returned should be the probability that
        * everyone in set `one_gene` has one copy of the gene, and
        * everyone in set `two_genes` has two copies of the gene, and
        * everyone not in `one_gene` or `two_gene` does not have the gene, and
        * everyone in set `have_trait` has the trait, and
        * everyone not in set` have_trait` does not have the trait.
    """
    all_people = set(people.keys())
    joint_prob = 1

    for person in all_people:
        p_person = 1
        mother = people[person]['mother']
        mother_count = 1 if mother in one_gene else 2 if mother in two_genes else 0
        father = people[person]['father']
        father_count = 1 if father in one_gene else 2 if father in two_genes else 0
        has_parent = mother is not None and father is not None
        gene_count = 1 if person in one_gene else 2 if person in two_genes else 0
        has_trait = True if person in have_trait else False

        if has_parent:
            # Probability for having gene_count is conditional on parents
            # gene_count = 0 -> P(not mother and not father)
            # gene_count = 1 -> P(mother or father) = P(mother and not father + not mother and father)
            # gene_count = 2 -> P(mother and father)
            if gene_count == 0:
                p_person *= PROBS["pass_down"][mother_count][0] * \
                    PROBS["pass_down"][father_count][0]
            elif gene_count == 1:
                p_person *= PROBS["pass_down"][mother_count][1] * PROBS["pass_down"][father_count][0] + \
                    PROBS["pass_down"][mother_count][0] * \
                    PROBS["pass_down"][father_count][1]
            else:
                p_person *= PROBS["pass_down"][mother_count][1] * \
                    PROBS["pass_down"][father_count][1]

            p_person *= PROBS["trait"][gene_count][has_trait]
        else:
            # Probability for having gene_count is purely unconditional
            p_person *= PROBS["gene"][gene_count]
            p_person *= PROBS["trait"][gene_count][has_trait]

        joint_prob *= p_person

    return joint_prob


def update(probabilities, one_gene, two_genes, have_trait, p):
    """
    Add to `probabilities` a new joint probability `p`.
    Each person should have their "gene" and "trait" distributions updated.
    Which value for each distribution is updated depends on whether
    the person is in `have_gene` and `have_trait`, respectively.
    """
    for person in probabilities.keys():
        gene_count = 1 if person in one_gene else 2 if person in two_genes else 0
        has_trait = True if person in have_trait else False

        probabilities[person]["gene"][gene_count] += p
        probabilities[person]["trait"][has_trait] += p


def normalize(probabilities):
    """
    Update `probabilities` such that each probability distribution
    is normalized (i.e., sums to 1, with relative proportions the same).
    """
    for _, person in probabilities.items():
        gene_probabilities_sum = sum(
            [value for _, value in person["gene"].items()])
        trait_probabilities_sum = sum(
            [value for _, value in person["trait"].items()])

        for key in person["gene"].keys():
            person["gene"][key] /= gene_probabilities_sum

        for key in person["trait"].keys():
            person["trait"][key] /= trait_probabilities_sum


if __name__ == "__main__":
    main()