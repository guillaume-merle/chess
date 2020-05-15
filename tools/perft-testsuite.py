from perft import perft
from chess import Board
import argparse
import sys
import os
import subprocess

good = 0
fail = 0

def print_test_result(test_name, ref_result, engine_result):
    print(f"{test_name.name}: ", end="")
    if ref_result == int(engine_result):
        print("OK.")
        global good
        good += 1
    else:
        print("KO.", f"Got {engine_result} but {ref_result} was expected")
        global fail
        fail += 1


def perft_test_file(perft_file_path, engine_dir_path):
    try:
        engine_perft = int(
            subprocess.run([os.path.join(engine_dir_path, 'chessengine'), '--perft', perft_file_path],
                       stdout=subprocess.PIPE,
                       encoding="utf-8").stdout)
    except Exception as e:
        raise Exception("Could not read the returned value from your chessengine. Check it is a valid number and it is printed to stdout")
    with open(perft_file_path) as p:
        perft_line = str.strip(p.readline())
        fen, depth = ' '.join(perft_line.split()[:-1]), perft_line.split()[-1]
        board = Board(fen)
        ref_perft = perft(int(depth), board)
        print_test_result(p, ref_perft, engine_perft)


def perft_test_directory(perft_dir_path, engine_dir_path):
    for perft_file in os.listdir(perft_dir_path):
        if perft_file.split('.')[-1] != "perft":
            continue
        perft_test_file(os.path.join(perft_dir_path, perft_file), engine_dir_path)
    print(f"Fail: {fail} / {fail + good}", f"Good: {good} / {fail + good}", sep='\n')


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Test your engine with perft.")
    parser.add_argument("perft_directory", type=str, help="A directory containing\
                         .perft files you want to test.")
    parser.add_argument("build_directory", type=str, help="The build directory containing\
                         your chessengine binary.")
    args = parser.parse_args()
    perft_test_directory(args.perft_directory, args.build_directory)
