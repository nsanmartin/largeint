#!/usr/bin/python3

import sys

def main(argv):

    n = int (argv[0], 16)
    times = int (argv[1])
    sum = 0
    for i in range(times):
        sum = sum + n
        
    print (hex (sum))


if __name__ == '__main__':
    if len(sys.argv) != 3:
        print("usage: add NUM NUM")
        sys.exit(0)

    else:
        main(sys.argv[1:])

