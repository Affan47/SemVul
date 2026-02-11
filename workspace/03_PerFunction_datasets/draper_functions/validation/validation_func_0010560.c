ntru_add_int_mod(NtruIntPoly *a, NtruIntPoly *b, int modulus) {
    int i;
    for (i=0; i<b->N; i++)
        a->coeffs[i] = (a->coeffs[i]+b->coeffs[i]) % modulus;
}
