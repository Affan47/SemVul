Dmatrix_new(int r, int c)
{
    Dmatrix V;

    V = (Dmatrix) mem_malloc(sizeof(struct Dmatrix_t));
    if (!V)
	bad_error("allocation failure in Dmatrix_new()");
    V->coords = (double *) mem_malloc(r * c * sizeof(double));
    if (!V)
	bad_error("allocation failure 2 in Dmatrix_new()");
    Mstore(V) = r * c;
    Mrows(V) = r;
    Mcols(V) = c;
    return V;
}
