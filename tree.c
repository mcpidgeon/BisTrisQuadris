#include "header.h"
#include <stdlib.h>

void buildRoot(struct Tree tree, int totalboards) {
	if (tree.depth == 0) {
		tree.root->self = totalboards-1-tree.root->self;
		tree.boards[tree.root->self] = tree.root;
	} else {
		tree.root->table = malloc(sizeof (struct Board) * tree.trisspace.squarecount);
		int newself = tree.root->self * tree.trisspace.squarecount + 1;
		for (int i=0; i<tree.trisspace.squarecount; i++) {
			*(tree.root->table+i) = (struct Board){newself+tree.trisspace.squarecount-1-i, tree.root, NULL, NULL, 0, 0};
			struct Tree subtree = tree;
			subtree.depth -= 1;
			subtree.root = tree.root->table+i;
			buildRoot(subtree, totalboards);
		}
		tree.root->self = totalboards-1-tree.root->self;
		tree.boards[tree.root->self] = tree.root;
	}
}

void fixNext(struct Tree tree) {
	if (tree.depth != 0) {
		for (int i=0; i<tree.trisspace.squarecount; i++) {
			struct Tree subtree = tree;
			subtree.depth -= 1;
			subtree.root = tree.root->table+i;
			if (tree.pointer != NULL) {
				subtree.pointer = tree.pointer->table+i;
			} else {
				subtree.pointer = tree.root;
			}
			(tree.root->table+i)->next = subtree.pointer;
			fixNext(subtree);
		}
	}
}

struct Tree generateTree(struct TrisSpace trisspace, int depth, int players) {
	struct Board* root = malloc(sizeof (struct Board));
	*root = (struct Board){0, NULL, NULL, NULL, 0, 0};
	struct Board** boards = malloc(sizeof (struct Board*) * sumpow(trisspace.squarecount, depth));
	struct Tree tree = {boards, trisspace, depth, players, root, NULL, 0};
	buildRoot(tree, sumpow(tree.trisspace.squarecount, tree.depth));
	fixNext(tree);
	tree.pointer = root;
	return tree;
}

void freeRoot(struct Tree tree) {
	if (tree.depth > 0) {
		for (int i=0; i<tree.trisspace.squarecount; i++) {
			struct Tree subtree = tree;
			subtree.depth = tree.depth - 1;
			subtree.root = tree.root->table+i;
			freeRoot(subtree);
		}
		free(tree.root->table);
	}
}

void freeTree(struct Tree tree) {
	free(tree.boards);
	free(tree.trisspace.topology);
	freeRoot(tree);
	free(tree.root);
}
