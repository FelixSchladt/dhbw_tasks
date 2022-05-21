// Copyright 2022 Thomas Gingele (https://github.com/Ginthom)

#include "iterative_binary_tree.h"

//This file contains a binary tree used to translate morse code to chars.
//The tree is stored in an array and i go through it iteratively while keeping the waya binary tree works for
//optimal performance.

//I wanted to include numbers as well so i extended the tree accordingly.
//The few special symbols that are still included in this range i have added as well, but anything on the next depth of the tree (e.g. '_') are not translatable.

//            DEPTH:   0    1         2                   3                                       4
//            KNOT :   0    1    2    3    4    5    6    7    8    9   10   11    12  13   14   15   16   17   18   19   20   21   22   23   24   25   26   27   28   29   30
//            CHAR :        .    -    .    -    .    -    .    -    .    -    .    -    .    -    .    -    .    -    .    -    .    -    .    -    .    -    .    -    .    -
const char tree[] =  {'-', 'E', 'T', 'I', 'A', 'N', 'M', 'S', 'U', 'R', 'W', 'D', 'K', 'G', 'O', 'H', 'V', 'F', 'U', 'L', 'A', 'P', 'J', 'B', 'X', 'C', 'Y', 'Z', 'Q', 'O', '-',
//             DEPTH:  5
//             KNOT : 31   32   33   34   35   36   37   38   39   40   41   42   43   44   45   46   47   48   49   50   51   52   53   54   55   56   57   58   59   60
//             CHAR :  .    -    .    -    .    -    .    -    .    -    .    -    .    -    .    -    .    -    .    -    .    -    .    -    .    -    .    -    .    -
	              '5', '4', '-', '3', 'E', '-', '-', '2', '&', 'E', '-', '-', '-', 'A', '-', '1', '6', '-', '/', '-', '-', '-', '(', '-', '7', '-', '-', 'N', '8', '-',
//             DEPTH:
//             KNOT : 61   62
//             CHAR :  .    -
                      '9', '0'};

int ipow(int base, int exponent) {
	int result = 1;
	for (int i = 0; i < exponent; i++) {
		result *= base;
	}
	return result;
}

int depth_index(int depth) {
	int result = 0;
	for (int i = 0; i <= depth && depth >= 0; i++) {
		result += ipow(2, i);
	}
	return result;
}

char morse_to_text(char* morse) {
	int depth   = 0;
	int index   = 0;
	int block   = 0;
	int is_line = 0;
	char result = '-';

	while(*morse == '.' || *morse == '-') {
		is_line = *morse == '.' ? 0 : 1;
		block   = index - ipow(2, depth) + 1;
		index = depth_index(depth) + block*2 + is_line;

		depth++;
		morse++;
		result = tree[index];
	}
	return result;
}
