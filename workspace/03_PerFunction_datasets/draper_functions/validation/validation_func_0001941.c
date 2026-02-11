mp_bpoly2arr(const mp_int *a, unsigned int p[], int max)
{
    int i, j, k;
    mp_digit top_bit, mask;

    top_bit = 1;
    top_bit <<= MP_DIGIT_BIT - 1;

    for (k = 0; k < max; k++) p[k] = 0;
    k = 0;

    for (i = MP_USED(a) - 1; i >= 0; i--) {
        mask = top_bit;
        for (j = MP_DIGIT_BIT - 1; j >= 0; j--) {
            if (MP_DIGITS(a)[i] & mask) {
                if (k < max) p[k] = MP_DIGIT_BIT * i + j;
                k++;
            }
            mask >>= 1;
        }
    }

    return k;
}
