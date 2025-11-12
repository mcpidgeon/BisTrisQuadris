#include "header.h"
#include <stdlib.h>

void updateOutcomes(struct Tree tree) {
	if (tree.pointer == tree.root || tree.pointer == NULL) {return;}
	struct Board* pointer = tree.pointer;
	int squarecount = tree.trisspace.squarecount, triscount = tree.trisspace.triscount;
	bool* topology = tree.trisspace.topology;
	pointer->parent->full += 1;
	bool trismade = false;
	if (pointer->outcome != 1) {
		int row = (pointer->self % squarecount) * triscount;
		for (int tris=0; tris<triscount; tris++) {
			if (topology[row + tris]) {
				bool flag = true;
				for (int square=0; square<squarecount; square++) {
					if (topology[square * triscount + tris]) {
						if (pointer->parent->table[square].outcome != pointer->outcome) {
							flag = false;
						}
					}
				}
				if (flag) {
					trismade = true;
					pointer->parent->outcome = pointer->outcome;
					struct Tree newtree = tree;
					newtree.pointer = pointer->parent;
					updateOutcomes(newtree);
					break;
				}
			}
		}
	}
	if (!trismade && pointer->parent->full == squarecount) {
		pointer->parent->outcome = 1;
		struct Tree newtree = tree;
		newtree.pointer = pointer->parent;
		updateOutcomes(newtree);
	}
}

struct Tree updatePointer(struct Tree tree) {
	struct Tree newtree = tree;
	newtree.pointer = newtree.pointer->next;
	while (newtree.pointer != NULL && newtree.pointer->outcome != 0) {
		newtree.pointer = newtree.pointer->parent;
	}
	return newtree;
}
