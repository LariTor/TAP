def print_board(board):
    for i in range(3):
        for j in range(3):
            print(board[i * 3 + j], end=" ")
        print("-----------------------------------------")


def check_winner(board):
    winning_combinations = [
        [0, 1, 2],
        [3, 4, 5],
        [6, 7, 8],  # Horizontales
        [0, 3, 6],
        [1, 4, 7],
        [2, 5, 8],  # Verticales
        [0, 4, 8],
        [2, 4, 6],  # Diagonales
    ]
    for comb in winning_combinations:
        if board[comb[0]] == board[comb[1]] == board[comb[2]] != 0:
            return board[comb[0]]
    return 0


def is_restricted_move(pos, restrictions, board):
    for a, b in restrictions:
        if pos == b - 1 and board[a - 1] == 0:
            return True
    return False


def backtrack(board, player, restrictions, memo):
    state = tuple(board)

    if state in memo:
        return memo[state]

    result = check_winner(board)
    if result != 0:
        return result, True

    if all(cell != 0 for cell in board):
        return 0, False

    best_result = -player
    winner_found = False

    for i in range(9):
        if board[i] == 0 and not is_restricted_move(i, restrictions, board):
            board[i] = player
            current_result, winner_found_aux = backtrack(
                board, -player, restrictions, memo
            )
            board[i] = 0

            if winner_found_aux:
                winner_found = True
            if player == 1:
                best_result = max(best_result, current_result)
            else:
                best_result = min(best_result, current_result)

    if not winner_found:
        best_result = 0

    memo[state] = (best_result, winner_found)
    return best_result, winner_found


def calc(n, restrictions):
    board = [0] * 9
    memo = {}

    final_result, _ = backtrack(board, 1, restrictions, memo)

    if final_result == 1:
        return "X"
    elif final_result == -1:
        return "O"
    else:
        return "E"


n = int(input())
restrictions = set()
for _ in range(n):
    a, b = map(int, input().split())
    restrictions.add((a, b))

print(calc(n, restrictions))
