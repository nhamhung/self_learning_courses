from logic import *

AKnight = Symbol("A is a Knight")
AKnave = Symbol("A is a Knave")

BKnight = Symbol("B is a Knight")
BKnave = Symbol("B is a Knave")

CKnight = Symbol("C is a Knight")
CKnave = Symbol("C is a Knave")

# Puzzle 0
# A says "I am both a knight and a knave."
A_statement0 = And(AKnight, AKnave)
knowledge0 = And(
    Or(AKnight, AKnave),
    Implication(AKnight, Not(AKnave)),
    Implication(AKnave, Not(AKnight)),
    Implication(AKnight, A_statement0),
    Implication(AKnave, Not(A_statement0))
)

# Puzzle 1
# A says "We are both knaves."
# B says nothing.
A_statement1 = And(AKnave, BKnave)
knowledge1 = And(
    Or(AKnight, AKnave),
    Implication(AKnight, Not(AKnave)),
    Implication(AKnave, Not(AKnight)),
    Implication(AKnight, A_statement1),
    Implication(AKnave, Not(A_statement1)),
    Or(BKnight, BKnave),
    Implication(BKnight, Not(BKnave)),
    Implication(BKnave, Not(BKnight))
)

# Puzzle 2
# A says "We are the same kind."
# B says "We are of different kinds."
A_statement2 = Or(And(AKnight, BKnight), And(AKnave, BKnave))
B_statement2 = Or(And(AKnight, BKnave), And(AKnave, BKnight))
knowledge2 = And(
    Or(AKnight, AKnave),
    Implication(AKnight, Not(AKnave)),
    Implication(AKnave, Not(AKnight)),
    Implication(AKnight, A_statement2),
    Implication(AKnave, Not(A_statement2)),
    Or(BKnight, BKnave),
    Implication(BKnight, Not(BKnave)),
    Implication(BKnave, Not(BKnight)),
    Implication(BKnight, B_statement2),
    Implication(BKnave, Not(B_statement2))
)

# Puzzle 3
# A says either "I am a knight." or "I am a knave.", but you don't know which.
# B says "A said 'I am a knave'."
# B says "C is a knave."
# C says "A is a knight."
knowledge3 = And(
    Or(AKnight, AKnave),
    Implication(AKnight, Not(AKnave)),
    Implication(AKnave, Not(AKnight)),
    Or(BKnight, BKnave),
    Implication(BKnight, Not(BKnave)),
    Implication(BKnave, Not(BKnight)),
    Implication(BKnight, And(CKnave, Not(Or(AKnight, AKnave)))),
    Implication(BKnave, And(CKnight, AKnight)),
    Or(CKnight, CKnave),
    Implication(CKnight, Not(CKnave)),
    Implication(CKnave, Not(CKnight)),
    Implication(CKnight, AKnight),
    Implication(CKnave, AKnave)
)


def main():
    symbols = [AKnight, AKnave, BKnight, BKnave, CKnight, CKnave]
    puzzles = [
        ("Puzzle 0", knowledge0),
        ("Puzzle 1", knowledge1),
        ("Puzzle 2", knowledge2),
        ("Puzzle 3", knowledge3)
    ]
    for puzzle, knowledge in puzzles:
        print(puzzle)
        if len(knowledge.conjuncts) == 0:
            print("    Not yet implemented.")
        else:
            for symbol in symbols:
                if model_check(knowledge, symbol):
                    print(f"    {symbol}")


if __name__ == "__main__":
    main()
