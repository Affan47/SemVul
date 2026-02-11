findsnake(int depth, long A, long N, long B, long M)
{
    snake_t         *sp;
    long            ulx = 0;
    long            uly = 0;
    long            lrx = 0;
    long            lry = 0;
    long            D;
    long            count;

    trace(("findsnake(depth = %d, A = %ld, N = %ld, B = %ld, M = %ld)\n{\n",
	depth, A, N, B, M));


    D = midsnake(A, N, B, M, &ulx, &uly, &lrx, &lry);

    if (D > 1)
    {
	if (ulx > 0 && uly > 0)
	    findsnake(depth + 1, A, ulx, B, uly);
	count = lrx - ulx;
	sp = nextsnake++;
	sp->line1 = A + ulx;
	sp->line2 = B + uly;
	sp->count = count;
	N -= lrx;
	M -= lry;
	if (N > 0 && M > 0)
	    findsnake(depth + 1, A + lrx, N, B + lry, M);
	trace(("}\n"));
	return;
    }


    if (N > M)
	count = uly;
    else
	count = ulx;
    sp = nextsnake++;
    sp->line1 = A;
    sp->line2 = B;
    sp->count = count;


    count = lrx - ulx;
    sp = nextsnake++;
    sp->line1 = A + ulx;
    sp->line2 = B + uly;
    sp->count = count;
    trace(("}\n"));
}
