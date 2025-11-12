#ifndef __HEADER_H_
#define __HEADER_H_

#include <stdbool.h>

//DEFINITIONS

typedef enum interface {
	TEXT, NCURSES, GRAPHICAL
} interface;

typedef enum builtin_space {
	NDGCUBE, STDCUBE, TRSCUBE
} builtin_space;

typedef struct TrisSpace {
	int squarecount; // numero di board per tabella
	int triscount; // numero totale di tris
	bool* topology; // tabella board-tris [DA LIBERARE]
} TrisSpace;

typedef struct Board {
	int self; // il suo indirizzo
	struct Board* parent; // il genitore
	struct Board* next; // la prossima griglia in ordine di gioco
	struct Board* table; // le griglie successive
	int full; // numero totale di segni presenti (anche DRAW)
	int outcome; // il risultato della griglia: 0=BLANK, 1=DRAW, 2=PLAYER1, ...
} Board;

typedef struct Tree {
	struct Board** boards; // una lista di tutti i puntatori alle board, ordinata by self
	struct TrisSpace trisspace; // il pattern
	int depth; // la profondita' totale
	int players; // il numero di giocatori
	struct Board* root; // la radice [DA LIBERARE]
	struct Board* pointer; // il puntatore
	int turn; // il giocatore corrente
} Tree;

//MATH

int npow(int base, int exp);
int sumpow(int base, int exp);
int fact(int n);
int bin(int n, int k);
int ithdigit(int n, int i, int base);

//FUNCTIONS

struct TrisSpace generateCube(enum builtin_space top, int edge, int dimensions);

struct Tree generateTree(struct TrisSpace trisspace, int depth, int players);
void freeTree(struct Tree tree);

enum interface getInterface();
struct Tree buildTree(enum interface itf);
void giveTurn(enum interface itf, struct Tree tree);
struct Tree setPointer(enum interface itf, struct Tree tree);
void giveTree(enum interface itf, struct Tree tree);
void giveOutcome(enum interface itf, struct Tree tree);

void updateOutcomes(struct Tree tree);
struct Tree updatePointer(struct Tree tree);

#endif
