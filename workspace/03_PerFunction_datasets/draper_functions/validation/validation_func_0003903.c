syncCards64(char *bmap) {
    long i = 0;
    unsigned long long *llong;

    while (i<numCards) {
        llong = (unsigned long long*)&bmap[i<<3];
        if ((unsigned long long)(*llong) == MAX64BIT)
            card[i] = (char)1;
        else
            card[i] = (char)0;
        i++;
    }
}
