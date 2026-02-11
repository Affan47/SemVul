ratio(uc, c)
    zusz_t uc, c;
{
    zusz_t denom;

    if (uc == 0)
        return 0;
    if (uc > 2000000L) {
        denom = uc / 1000L;
        return ((uc >= c) ?
            (int) ((uc-c + (denom>>1)) / denom) :
          -((int) ((c-uc + (denom>>1)) / denom)));
    } else {
        denom = uc;
        return ((uc >= c) ?
            (int) ((1000L*(uc-c) + (denom>>1)) / denom) :
          -((int) ((1000L*(c-uc) + (denom>>1)) / denom)));
    }
}
