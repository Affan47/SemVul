do_gen(loopstruct * lp)
{
	int         i, j, k;
	unsigned char *z;
	unsigned int n[MAXNEIGHBORS];
	unsigned int c;

#define LOC(X, Y) (*(lp->oldcells + (X) + ((Y) * lp->bncols)))

	for (j = lp->minrow; j <= lp->maxrow; j++) {
		for (i = lp->mincol; i <= lp->maxcol; i++) {
			z = lp->newcells + i + j * lp->bncols;
			c = LOC(i, j);
			for (k = 0; k < local_neighbors; k++) {
				int         newi = i, newj = j;

				position_of_neighbor(k * ANGLES / local_neighbors, &newi, &newj);
				n[k] = 0;
		    if (withinBounds(lp, newi, newj)) {
					n[k] = LOC(newi, newj);
				}
			}
			if (local_neighbors == 6) {
				*z = (lp->clockwise) ?
					HEX_TABLE_OUT(c, n[5], n[4], n[3], n[2], n[1], n[0]) :
					HEX_TABLE_OUT(c, n[0], n[1], n[2], n[3], n[4], n[5]);
			} else {
				*z = (lp->clockwise) ?
					TABLE_OUT(c, n[3], n[2], n[1], n[0]) :
					TABLE_OUT(c, n[0], n[1], n[2], n[3]);
			}
		}
	}
}
