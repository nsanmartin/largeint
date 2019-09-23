#!/usr/bin/python3

import sys

def main(argv):

    x = int (argv[0], 16)
    y = int (argv[1], 16)
    print ( hex (x + y))q


if __name__ == '__main__':
    if len(sys.argv) != 3:
        print("usage: add NUM NUM")
        sys.exit(0)

    else:
        main(sys.argv[1:])

