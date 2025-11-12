#include "header.h"
#include <stdlib.h>

//GENERIC

struct TrisSpace nodiagonals(int edge, int dimensions);
struct TrisSpace standard(int edge, int dimensions);
struct TrisSpace torus(int edge, int dimensions);

struct TrisSpace generateCube(enum builtin_space space, int edge, int dimensions) {
	struct TrisSpace trisspace;
	switch (space) {
	case NDGCUBE:
		trisspace = nodiagonals(edge, dimensions);
		break;
	case STDCUBE:
		trisspace = standard(edge, dimensions);
		break;
	case TRSCUBE:
		trisspace = torus(edge, dimensions);
		break;
	default:
		trisspace = (struct TrisSpace){0, 0, NULL};
		break;
	}
	return trisspace;
}

//NODIAGONALS

struct TrisSpace nodiagonals(int edge, int dimensions) {
	struct TrisSpace trisspace = {npow(edge, dimensions), npow(edge, dimensions-1) * dimensions, NULL};
	trisspace.topology = calloc(trisspace.squarecount * trisspace.triscount, sizeof (bool));
	int trisid = 0;
	for (int n=0; n<dimensions; n++) {
		int basevector = npow(edge, n);
		for (int probe=0; probe<npow(edge, dimensions-1); probe++) {
			for (int i=0; i<edge; i++) {
				int squarexyz = edge * (probe / basevector) + i*basevector + probe % basevector;
				trisspace.topology[squarexyz * trisspace.triscount + trisid] = true;
			}
			trisid += 1;
		}
	}
	return trisspace;
}

//STANDARD

int standardTrisCount(int edge, int dimensions) {
	int result = 0;
	int e = edge, d = dimensions;
	for (int k = 1; k<=d; k++) {
		result += bin(d,k)*npow(2,k-1)*npow(e,d-k);
	}
	return result;
}

struct TrisSpace standard(int edge, int dimensions) {
	struct TrisSpace trisspace = {npow(edge, dimensions), standardTrisCount(edge, dimensions), NULL};
	trisspace.topology = calloc(trisspace.squarecount * trisspace.triscount, sizeof (bool));
	int trisid = 0;
	for (int vars=1; vars<npow(2,dimensions); vars++) {
		int ones = 0;
		for (int mask = 1; mask<npow(2,dimensions); mask <<= 1) {
			if (vars & mask) {
				ones += 1;
			}
		}
		for (int posneg = npow(2, ones-1); posneg < npow(2, ones); posneg++) {
			int fixed = 0;
			int step = 0;
			for (int mask=1, pnmask=1, basevector=1; mask<npow(2,dimensions); mask<<=1, basevector*=edge) {
				if (vars & mask) {
					if (posneg & pnmask) {
						step += basevector;
					} else {
						fixed += basevector * (edge-1);
						step -= basevector;
					}
					pnmask <<= 1;
				} 
			}
			for (int probe = 0; probe<npow(edge, dimensions-ones); probe++) {
				int squarexyz = fixed;
				int probeclone = probe;
				for (int mask=1, basevector=1; mask<npow(2,dimensions); mask<<=1, basevector*=edge) {
					if (!(vars & mask)) {
						squarexyz += (probeclone % edge) * basevector;
						probeclone /= edge;
					}
				}
				for (int i=0; i<edge; i++) {
					trisspace.topology[squarexyz * trisspace.triscount + trisid] = true;
					squarexyz += step;
				}
				trisid += 1;
			}
		}
	}
	return trisspace;
}

//TORUS

struct TrisSpace torus(int edge, int dimensions) {
	struct TrisSpace trisspace = {npow(edge, dimensions), ((npow(3, dimensions)-1) / 2) * npow(edge, dimensions-1), NULL};
	trisspace.topology = calloc(trisspace.squarecount * trisspace.triscount, sizeof (bool));
	int trisid = 0;
	for (int vars=1; vars<npow(2,dimensions); vars++) {
		int ones = 0;
		int firstone = 0;
		for (int mask = 1, index=0; mask<npow(2,dimensions); mask<<=1, index++) {
			if (vars & mask) {
				ones += 1;
				firstone=index;
			}
		}
		for (int posneg = npow(2, ones-1); posneg < npow(2, ones); posneg++) {
			int posstep = 0;
			int negstep = 0;
			for (int mask=1, pnmask=1, basevector=1, index=0; mask<npow(2,dimensions); mask<<=1, basevector*=edge, index++) {
				if (vars & mask) {
					if (posneg & pnmask) {
						posstep += basevector;
					} else {
						negstep += basevector;
					}
					pnmask <<= 1;
				}
			}
			for (int probe = 0; probe<npow(edge, dimensions-1); probe++) {
				int squarexyz = 0;
				int probeclone = probe;
				for (int index=0, basevector=1; index<dimensions; index++, basevector*=edge) {
					if (index != firstone) {
						squarexyz += (probeclone % edge) * basevector;
						probeclone /= edge;
					}
				}
				for (int i=0; i<edge; i++) {
					trisspace.topology[squarexyz * trisspace.triscount + trisid] = true;
					int newxyz = squarexyz;
					for (int j=0; j<dimensions; j++) {
						int x = ithdigit(squarexyz, j, edge) + ithdigit(posstep, j, edge) - ithdigit(negstep, j, edge);
						if (x>=edge) {
							newxyz -= npow(edge, j+1);
						} else if (x<0) {
							newxyz += npow(edge, j+1);
						}
					}
					squarexyz = newxyz;
					squarexyz += posstep - negstep;
				}
				trisid += 1;
			}
		}
	}
	return trisspace;
}
