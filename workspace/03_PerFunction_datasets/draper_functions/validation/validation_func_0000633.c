count_pieces(PIX  *pix, l_int32 nexp)
{
l_int32  n;
BOXA    *boxa;

    pixDisplayWrite(pix, 1);
    boxa = pixConnComp(pix, NULL, 8);
    n = boxaGetCount(boxa);
    if (n == nexp)
        fprintf(stderr, "Correct: Num. comps: %d\n", n);
    else
        fprintf(stderr, "WRONG!: Num. comps: %d\n", n);
    boxaDestroy(&boxa);
    pixDestroy(&pix);
}
