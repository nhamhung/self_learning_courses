"""
Tic Tac Toe Player
"""

import math
import copy

X = "X"
O = "O"
EMPTY = None


def initial_state():
    """
    Returns starting state of the board.
    """
    return [[EMPTY, EMPTY, EMPTY],
            [EMPTY, EMPTY, EMPTY],
            [EMPTY, EMPTY, EMPTY]]


def player(board):
    """
    Returns player who has the next turn on a board.
    """
    x_count = sum([1 for row in board for player in row if player == X])
    o_count = sum([1 for row in board for player in row if player == O])

    return X if x_count == o_count else O


def actions(board):
    """
    Returns set of all possible actions (i, j) available on the board.
    """
    result = []

    for i in range(3):
        for j in range(3):
            if board[i][j] == EMPTY:
                result.append((i, j))

    return set(result)


def result(board, action):
    """
    Returns the board that results from making move (i, j) on the board.
    """
    i, j = action

    if i < 0 or j < 0 or i > 2 or j > 2 or board[i][j] != EMPTY:
        raise Exception

    board_copy = copy.deepcopy(board)

    board_copy[i][j] = player(board_copy)

    return board_copy


def winner(board):
    """
    Returns the winner of the game, if there is one.
    """
    all_directions = get_all_directions(board)

    for direction in all_directions:
        if direction[0] != EMPTY and all(element == direction[0] for element in direction):
            return direction[0]

    return None


def get_all_directions(board):
    rows = [board[i] for i in range(3)]
    cols = [[board[i][j] for i in range(3)] for j in range(3)]
    first_diagonal = [board[i][i] for i in range(3)]
    second_diagonal = [board[2 - i][i] for i in range(3)]

    all_directions = rows + cols + [first_diagonal, second_diagonal]

    return all_directions


def terminal(board):
    """
    Returns True if game is over, False otherwise.
    """
    if winner(board):
        return True

    for row in board:
        for cell in row:
            if cell == EMPTY:
                return False

    return True


def utility(board):
    """
    Returns 1 if X has won the game, -1 if O has won, 0 otherwise.
    """
    if winner(board) == X:
        return 1
    elif winner(board) == O:
        return -1
    else:
        return 0


def get_lowest_index(lst):
    min_value = float('inf')
    lowest_index = None

    for i, value in enumerate(lst):
        if value < min_value:
            min_value = value
            lowest_index = i

    return lowest_index


def get_highest_index(lst):
    max_value = float('-inf')
    highest_index = None

    for i, value in enumerate(lst):
        if value > max_value:
            max_value = value
            highest_index = i

    return highest_index


def minimax(board):
    """
    Returns the optimal action for the current player on the board.
    """
    def max_value(board):
        if terminal(board):
            return utility(board)

        v = float('-inf')

        for action in actions(board):
            v = max(v, min_value(result(board, action)))

        return v

    def min_value(board):
        if terminal(board):
            return utility(board)

        v = float('inf')

        for action in actions(board):
            v = min(v, max_value(result(board, action)))

        return v

    if terminal(board):
        return None

    valid_actions = list(actions(board))
    valid_action_values = []

    if player(board) == X:
        for action in valid_actions:
            valid_action_values.append(min_value(result(board, action)))

        return valid_actions[get_highest_index(valid_action_values)]
    else:
        for action in valid_actions:
            valid_action_values.append(max_value(result(board, action)))

        return valid_actions[get_lowest_index(valid_action_values)]
