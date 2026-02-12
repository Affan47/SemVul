int ossl_rsaz_mod_exp_avx512_x2(BN_ULONG *res1,
                                const BN_ULONG *base1,
                                const BN_ULONG *exp1,
                                const BN_ULONG *m1,
                                const BN_ULONG *rr1,
                                BN_ULONG k0_1,
                                BN_ULONG *res2,
                                const BN_ULONG *base2,
                                const BN_ULONG *exp2,
                                const BN_ULONG *m2,
                                const BN_ULONG *rr2,
                                BN_ULONG k0_2,
                                int factor_size)
{
    int ret = 0;


    int exp_digits = number_of_digits(factor_size + 2, DIGIT_SIZE);
    int coeff_pow = 4 * (DIGIT_SIZE * exp_digits - factor_size);
    BN_ULONG *base1_red, *m1_red, *rr1_red;
    BN_ULONG *base2_red, *m2_red, *rr2_red;
    BN_ULONG *coeff_red;
    BN_ULONG *storage = NULL;
    BN_ULONG *storage_aligned = NULL;
    BN_ULONG storage_len_bytes = 7 * exp_digits * sizeof(BN_ULONG);


    AMM52 amm = NULL;

    EXP52_x2 exp_x2 = NULL;

    const BN_ULONG *exp[2] = {0};
    BN_ULONG k0[2] = {0};


    switch (factor_size) {
    case 1024:
        amm = ossl_rsaz_amm52x20_x1_256;
        exp_x2 = RSAZ_exp52x20_x2_256;
        break;
    default:
        goto err;
    }

    storage = (BN_ULONG *)OPENSSL_malloc(storage_len_bytes + 64);
    if (storage == NULL)
        goto err;
    storage_aligned = (BN_ULONG *)ALIGN_OF(storage, 64);


    base1_red = storage_aligned;
    base2_red = storage_aligned + 1 * exp_digits;
    m1_red    = storage_aligned + 2 * exp_digits;
    m2_red    = storage_aligned + 3 * exp_digits;
    rr1_red   = storage_aligned + 4 * exp_digits;
    rr2_red   = storage_aligned + 5 * exp_digits;
    coeff_red = storage_aligned + 6 * exp_digits;


    to_words52(base1_red, exp_digits, base1, factor_size);
    to_words52(base2_red, exp_digits, base2, factor_size);
    to_words52(m1_red, exp_digits, m1, factor_size);
    to_words52(m2_red, exp_digits, m2, factor_size);
    to_words52(rr1_red, exp_digits, rr1, factor_size);
    to_words52(rr2_red, exp_digits, rr2, factor_size);


    memset(coeff_red, 0, exp_digits * sizeof(BN_ULONG));

    set_bit(coeff_red, 64 * (int)(coeff_pow / 52) + coeff_pow % 52);

    amm(rr1_red, rr1_red, rr1_red, m1_red, k0_1);
    amm(rr1_red, rr1_red, coeff_red, m1_red, k0_1);

    amm(rr2_red, rr2_red, rr2_red, m2_red, k0_2);
    amm(rr2_red, rr2_red, coeff_red, m2_red, k0_2);

    exp[0] = exp1;
    exp[1] = exp2;

    k0[0] = k0_1;
    k0[1] = k0_2;

    exp_x2(rr1_red, base1_red, exp, m1_red, rr1_red, k0);


    from_words52(res1, factor_size, rr1_red);
    from_words52(res2, factor_size, rr2_red);


    factor_size /= sizeof(BN_ULONG) * 8;

    bn_reduce_once_in_place(res1, 0, m1, storage, factor_size);
    bn_reduce_once_in_place(res2, 0, m2, storage, factor_size);

    ret = 1;
err:
    if (storage != NULL) {
        OPENSSL_cleanse(storage, storage_len_bytes);
        OPENSSL_free(storage);
    }
    return ret;
}
