#include "header.h"

int main() {
	enum interface itf = getInterface();
	struct Tree tree = buildTree(itf);
	while (tree.root->outcome == 0) {
		tree = setPointer(itf, tree);
		tree.pointer->outcome = tree.turn+2;
		updateOutcomes(tree);
		tree = updatePointer(tree);
		tree.turn = (tree.turn + 1) % tree.players;
	}
	giveTree(itf, tree);
	giveOutcome(itf, tree);
	freeTree(tree);
	return 0;
}
