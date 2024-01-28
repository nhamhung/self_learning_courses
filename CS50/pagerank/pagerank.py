import os
import random
import re
import sys
from collections import Counter
import copy

DAMPING = 0.85
SAMPLES = 10000


def main():
    if len(sys.argv) != 2:
        sys.exit("Usage: python pagerank.py corpus")
    corpus = crawl(sys.argv[1])
    ranks = sample_pagerank(corpus, DAMPING, SAMPLES)
    print(f"PageRank Results from Sampling (n = {SAMPLES})")
    for page in sorted(ranks):
        print(f"  {page}: {ranks[page]:.4f}")
    ranks = iterate_pagerank(corpus, DAMPING)
    print(f"PageRank Results from Iteration")
    for page in sorted(ranks):
        print(f"  {page}: {ranks[page]:.4f}")


def crawl(directory):
    """
    Parse a directory of HTML pages and check for links to other pages.
    Return a dictionary where each key is a page, and values are
    a list of all other pages in the corpus that are linked to by the page.
    """
    pages = dict()

    # Extract all links from HTML files
    for filename in os.listdir(directory):
        if not filename.endswith(".html"):
            continue
        with open(os.path.join(directory, filename)) as f:
            contents = f.read()
            links = re.findall(r"<a\s+(?:[^>]*?)href=\"([^\"]*)\"", contents)
            pages[filename] = set(links) - {filename}

    # Only include links to other pages in the corpus
    for filename in pages:
        pages[filename] = set(
            link for link in pages[filename]
            if link in pages
        )

    return pages


def transition_model(corpus, page, damping_factor):
    """
    Return a probability distribution over which page to visit next,
    given a current page.

    With probability `damping_factor`, choose a link at random
    linked to by `page`. With probability `1 - damping_factor`, choose
    a link at random chosen from all pages in the corpus.
    """
    n = len(corpus)
    n_neighbors = len(corpus[page])

    model = {}

    non_neighbor_pages = set(corpus.keys()) - corpus[page]

    for non_neighbor in non_neighbor_pages:
        model[non_neighbor] = (1 - damping_factor) / n

    for neighbor in corpus[page]:
        model[neighbor] = damping_factor / \
            n_neighbors + (1 - damping_factor) / n

    return model


def sample_pagerank(corpus, damping_factor, n):
    """
    Return PageRank values for each page by sampling `n` pages
    according to transition model, starting with a page at random.

    Return a dictionary where keys are page names, and values are
    their estimated PageRank value (a value between 0 and 1). All
    PageRank values should sum to 1.
    """
    samples = []

    sample = list(corpus.keys())[random.randint(0, len(corpus) - 1)]
    samples.append(sample)

    for _ in range(1, n):
        model = transition_model(corpus, sample, damping_factor)
        population = list(model.keys())
        weights = list(model.values())
        sample = random.choices(population, weights, k=1)[0]
        samples.append(sample)

    counter = Counter(samples)

    pagerank = {}

    for value, count in counter.items():
        pagerank[value] = count / n

    return pagerank


def iterate_pagerank(corpus, damping_factor):
    """
    Return PageRank values for each page by iteratively updating
    PageRank values until convergence.

    Return a dictionary where keys are page names, and values are
    their estimated PageRank value (a value between 0 and 1). All
    PageRank values should sum to 1.
    """
    n = len(corpus)
    pagerank = {page: 1/n for page in corpus.keys()}
    inward_links = {}
    corpus_copy = copy.deepcopy(corpus)

    for page, neighbors in corpus.items():
        if not neighbors:
            corpus_copy[page] = set(list(corpus.keys()))

    for page, neighbors in corpus_copy.items():
        for neighbor in neighbors:
            if neighbor not in inward_links:
                inward_links[neighbor] = set()
                inward_links[neighbor].add(page)
            else:
                inward_links[neighbor].add(page)

    should_repeat = True

    while should_repeat:
        should_repeat = False
        for page, rank in pagerank.items():
            inward_neighbors = inward_links[page]
            sum_inward_probability = sum(
                [pagerank[inward_neighbor]/len(corpus_copy[inward_neighbor]) for inward_neighbor in inward_neighbors])
            new_rank = (1 - damping_factor) / n + \
                damping_factor * sum_inward_probability

            pagerank[page] = new_rank

            if abs(rank - new_rank) >= 0.001:
                should_repeat = True

    return pagerank


if __name__ == "__main__":
    main()
