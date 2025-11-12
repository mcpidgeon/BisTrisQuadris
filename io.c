#include "header.h"
#include <stdlib.h>
#include <stdio.h>

enum interface getInterface() {
	return TEXT;
}

struct Tree buildTree(enum interface itf) {
	struct TrisSpace trisspace;
	int depth, players;
	struct Tree tree;
	switch (itf) {
	default:
		printf("Which tris space do you want? (0: ndgcube, 1: stdcube, 2: trscube) ");
		int spaceindex;
		enum builtin_space space;
not_valid:
		scanf("%d", &spaceindex);
		switch (spaceindex) {
		case 0:
			space = NDGCUBE;
			break;
		case 1:
			space = STDCUBE;
			break;
		case 2:
			space = TRSCUBE;
			break;
		default:
			printf("\nYour choice is not valid. Try again: ");
			goto not_valid;
		}
		printf("\n");
		switch (space) {
		case NDGCUBE:
		case STDCUBE:
		case TRSCUBE:
			int edge, dimensions;
			printf("What's your cube's edge length? ");
			scanf("%d", &edge);
			while (edge < 2) {
				printf("\nYour edge length is not valid. Try again: ");
				scanf("%d", &edge);
			}
			printf("\nHow many dimensions does it live in? ");
			scanf("%d", &dimensions);
			while (dimensions < 1) {
				printf("\nYour answer is not valid. Try again: ");
				scanf("%d", &dimensions);
			}
			printf("\n");
			trisspace = generateCube(space, edge, dimensions);
			break;
		}
		printf("What's your tree's depth? ");
		scanf("%d", &depth);
		while (depth < 1) {
			printf("\nYour depth is not valid. Try again: ");
			scanf("%d", &depth);
		}
		printf("\nHow many players? ");
		scanf("%d", &players);
		while (players < 2) {
			printf("\nNot enough players. Try again: ");
			scanf("%d", &players);
		}
		printf("\n");
		break;
	}
	tree = generateTree(trisspace, depth, players);
	return tree;
}

void giveTurn(enum interface itf, struct Tree tree) {
	switch (itf) {
	default:
		printf("It's player %d's turn.\n", tree.turn);
		break;
	}
}

void printLocation(struct Tree tree) {
	printf("You're at: root");
	int selfcopy = tree.pointer->self;
	int check = npow(tree.trisspace.squarecount, tree.depth);
	while (check>1 && selfcopy >= check) {
		selfcopy -= check;
		check /= tree.trisspace.squarecount;
	}
	while (check>1) {
		check /= tree.trisspace.squarecount;
		printf("->[%d]", ((selfcopy % (check * tree.trisspace.squarecount)) - (selfcopy % check)) / check);
	}
	printf("\n");
}

int askAddress(enum interface itf, struct Tree tree) {
	int address;
	switch (itf) {
	default:
		printLocation(tree);
		printf("Where's your next move? ");
		scanf("%d", &address);
		printf("\n");
		while (address < 0 || address >= tree.trisspace.squarecount || tree.pointer->table[address].outcome != 0) {
			printf("Your address is not valid. Please enter another one: ");
			scanf("%d", &address);
			printf("\n");
		}
		break;
	}
	return address;
}

struct Tree setPointer(enum interface itf, struct Tree tree) {
	struct Tree newtree = tree;
	while (newtree.pointer->table != NULL) {
		giveTree(itf, newtree);
		giveTurn(itf, newtree);
		int address = askAddress(itf, newtree);
		newtree.pointer = newtree.pointer->table+address;
	}
	return newtree;
}

void giveTree(enum interface itf, struct Tree tree) {
	switch (itf) {
	default:
		int flag = npow(tree.trisspace.squarecount, tree.depth);
		int mult = 1;
		for (int i = 0; i<sumpow(tree.trisspace.squarecount, tree.depth); i++) {
			if ((i+1) % (flag * tree.trisspace.squarecount) > flag) {
				flag /= tree.trisspace.squarecount;
				mult *= tree.trisspace.squarecount;
				printf("\n\n------\n\n");
			} else {
				for (int j = 1; i>=j && i%j == 0; j *= tree.trisspace.squarecount) {
					if (j == 1) {
						printf(" ");
					} else {
						printf("\n");
					}
				}
			}
			switch (tree.boards[i]->outcome) {
			case 0:
				printf("·");
				break;
			case 1:
				printf("X");
				break;
			default:
				printf("%d", tree.boards[i]->outcome-2);
				break;
			}
			if (tree.pointer != NULL && i%tree.trisspace.squarecount == tree.trisspace.squarecount-1 && tree.boards[i] != tree.root && tree.pointer->self == tree.boards[i]->parent->self) {
				printf(" <-- You're here");
			}
		}
		printf("\n\n");
		break;
	}
}

void giveOutcome(enum interface itf, struct Tree tree) {
	switch (itf) {
	default:
		switch (tree.root->outcome) {
			case 0:
				printf("The outcome is not yet clear.\n");
				break;
			case 1:
				printf("The game is a draw.\n");
				break;
			default:
				printf("Player %d has won the game. Congrats!\n", tree.root->outcome-2);
				break;
		}
		break;
	}
}
