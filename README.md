# BisTrisQuadris

> [!Important]
> This is my first project with multiple files, and my first GitHub repo, so forgive me if I made poor design choices or did not give sufficient documentation. Any suggestion is much appreciated!

BisTrisQuadris is a program to play a generalized version of tic tac toe. It was built for a coding competition among friends, but, depending on the will of its contributors, it could become a larger project, possibly hosting tic tac toe games over the network.

As of now, the program has a text interface (each board is represented as a line), but I'm planning on making a web app for it, with 2d and 3d visualization, and possibly an NCURSES interface as well. Another feature that I might add is a Python API, in order to make it easier for everyone to build an AI tic tac toe engine.

## Abstract representation
Its barebones structure consists of:

- **Tris space**: a finite set with n elements, together with a collection of arbitrarily chosen subsets of it.
- **Tree**: an n-ary tree of arbitrary depth, with additional oriented edges.
- **Match status**: A turn indicator, a pointer to the current node in the tree, and outcomes (BLANK, DRAW, PLAYER 0, ...) of each node.

The tris space is the abstract representation of a tic tac toe board: the n elements are the squares of the board (n=9 in the usual 3x3 board), and the chosen subsets are those that need to be checked to see if the outcome of the board has changed (the rows, columns and diagonals in the usual board).

The tree embodies the nested structure of such boards, as in ultimate tic tac toe (in which case depth=2), but generalized to an arbitrary depth. The additional edges tell us where to move the pointer after a symbol is placed, another concept in ultimate tic tac toe which has also been generalized.

The match status is the representation of the current state of a match.

## Capabilities

Thanks to the generality of the code, users can choose many different versions of tic tac toe to play. One can come up with whatever tris space they'd like to play on, but can also opt for one of the default ones. For example, constructors for cubes of arbitrary dimension with both standard and non-standard subset choices have already been made. Depth can too be chosen at will, and so can the number of players.

## License

[GPLv3](LICENSE)
