Allocate(int ACount) {
    PELine *L;

    if (ACount > 10 * 1024 * 1024)
        return 0;

    L = (PELine *) realloc(LL, sizeof(PELine) * (ACount + 1));
    if (!L && ACount != 0)
        return 0;
    RAllocated = ACount;
    LL = L;

    return 1;
}
