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
    typedef void (*AMM)(BN_ULONG *res, const BN_ULONG *a,
                        const BN_ULONG *b, const BN_ULONG *m, BN_ULONG k0);
    int ret = 0;


    int exp_digits = number_of_digits(factor_size + 2, DIGIT_SIZE);
    int coeff_pow = 4 * (DIGIT_SIZE * exp_digits - factor_size);


    int ymm_regs_num = NUMBER_OF_REGISTERS(exp_digits, 256 );

    int regs_capacity = ymm_regs_num * 4;

    BN_ULONG *base1_red, *m1_red, *rr1_red;
    BN_ULONG *base2_red, *m2_red, *rr2_red;
    BN_ULONG *coeff_red;
    BN_ULONG *storage = NULL;
    BN_ULONG *storage_aligned = NULL;
    int storage_len_bytes = 7 * regs_capacity * sizeof(BN_ULONG)
                           + 64 ;

    const BN_ULONG *exp[2] = {0};
    BN_ULONG k0[2] = {0};

    AMM amm = NULL;

    switch (factor_size) {
    case 1024:
        amm = ossl_rsaz_amm52x20_x1_ifma256;
        break;
    case 1536:
        amm = ossl_rsaz_amm52x30_x1_ifma256;
        break;
    case 2048:
        amm = ossl_rsaz_amm52x40_x1_ifma256;
        break;
    default:
        goto err;
    }

    storage = (BN_ULONG *)OPENSSL_malloc(storage_len_bytes);
    if (storage == NULL)
        goto err;
    storage_aligned = (BN_ULONG *)ALIGN_OF(storage, 64);


    base1_red = storage_aligned;
    base2_red = storage_aligned + 1 * regs_capacity;
    m1_red    = storage_aligned + 2 * regs_capacity;
    m2_red    = storage_aligned + 3 * regs_capacity;
    rr1_red   = storage_aligned + 4 * regs_capacity;
    rr2_red   = storage_aligned + 5 * regs_capacity;
    coeff_red = storage_aligned + 6 * regs_capacity;


    to_words52(base1_red, regs_capacity, base1, factor_size);
    to_words52(base2_red, regs_capacity, base2, factor_size);
    to_words52(m1_red,    regs_capacity, m1,    factor_size);
    to_words52(m2_red,    regs_capacity, m2,    factor_size);
    to_words52(rr1_red,   regs_capacity, rr1,   factor_size);
    to_words52(rr2_red,   regs_capacity, rr2,   factor_size);


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


    ret = RSAZ_mod_exp_x2_ifma256(rr1_red, base1_red, exp, m1_red, rr1_red,
                                  k0, factor_size);
    if (!ret)
        goto err;


    from_words52(res1, factor_size, rr1_red);
    from_words52(res2, factor_size, rr2_red);


    factor_size /= sizeof(BN_ULONG) * 8;

    bn_reduce_once_in_place(res1, 0, m1, storage, factor_size);
    bn_reduce_once_in_place(res2, 0, m2, storage, factor_size);

err:
    if (storage != NULL) {
        OPENSSL_cleanse(storage, storage_len_bytes);
        OPENSSL_free(storage);
    }
    return ret;
}
