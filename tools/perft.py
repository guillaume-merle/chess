import argparse
import sys
from chess import Board


def perft(depth, board):
    if depth == 1:
        return len(list(board.legal_moves))

    res = 0
    for move in board.legal_moves:
        board.push(move)
        res += perft(depth - 1, board)
        board.pop()

    return res


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="Compute perft value for a given perft file.")
    parser.add_argument("perft_file", type=str, help="Path to the perft file")
    args = parser.parse_args()
    with open(args.perft_file) as f:
        perft_line = str.strip(f.readline())
        fen, depth = ' '.join(perft_line.split()[:-1]), perft_line.split()[-1]
        board = Board(fen)
    print(perft(int(depth), board))
