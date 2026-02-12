int RSAZ_mod_exp_x2_ifma256(BN_ULONG *out,
                            const BN_ULONG *base,
                            const BN_ULONG *exp[2],
                            const BN_ULONG *m,
                            const BN_ULONG *rr,
                            const BN_ULONG k0[2],
                            int modulus_bitsize)
{
    typedef void (*DAMM)(BN_ULONG *res, const BN_ULONG *a,
                         const BN_ULONG *b, const BN_ULONG *m,
                         const BN_ULONG k0[2]);
    typedef void (*DEXTRACT)(BN_ULONG *res, const BN_ULONG *red_table,
                             int red_table_idx, int tbl_idx);

    int ret = 0;
    int idx;


    int exp_win_size = 5;
    int exp_win_mask = (1U << exp_win_size) - 1;


    int red_digits = 0;
    int exp_digits = 0;

    BN_ULONG *storage = NULL;
    BN_ULONG *storage_aligned = NULL;
    int storage_len_bytes = 0;


    BN_ULONG *red_Y = NULL;
    BN_ULONG *red_X = NULL;

    BN_ULONG *red_table = NULL;

    BN_ULONG *expz = NULL;


    DAMM damm = NULL;

    DEXTRACT extract = NULL;


# define DAMS(r,a,m,k0) damm((r),(a),(a),(m),(k0))

    switch (modulus_bitsize) {
    case 1024:
        red_digits = 20;
        exp_digits = 16;
        damm = ossl_rsaz_amm52x20_x2_ifma256;
        extract = ossl_extract_multiplier_2x20_win5;
        break;
    case 1536:

        red_digits = 30 + 2;
        exp_digits = 24;
        damm = ossl_rsaz_amm52x30_x2_ifma256;
        extract = ossl_extract_multiplier_2x30_win5;
        break;
    case 2048:
        red_digits = 40;
        exp_digits = 32;
        damm = ossl_rsaz_amm52x40_x2_ifma256;
        extract = ossl_extract_multiplier_2x40_win5;
        break;
    default:
        goto err;
    }

    storage_len_bytes = (2 * red_digits
                       + 2 * red_digits
                       + 2 * red_digits * (1U << exp_win_size)
                       + 2 * (exp_digits + 1))
                       * sizeof(BN_ULONG)
                       + 64;

    storage = (BN_ULONG *)OPENSSL_zalloc(storage_len_bytes);
    if (storage == NULL)
        goto err;
    storage_aligned = (BN_ULONG *)ALIGN_OF(storage, 64);

    red_Y     = storage_aligned;
    red_X     = red_Y + 2 * red_digits;
    red_table = red_X + 2 * red_digits;
    expz      = red_table + 2 * red_digits * (1U << exp_win_size);


    red_X[0 * red_digits] = 1;
    red_X[1 * red_digits] = 1;
    damm(&red_table[0 * 2 * red_digits], (const BN_ULONG*)red_X, rr, m, k0);
    damm(&red_table[1 * 2 * red_digits], base,  rr, m, k0);

    for (idx = 1; idx < (int)((1U << exp_win_size) / 2); idx++) {
        DAMS(&red_table[(2 * idx + 0) * 2 * red_digits],
             &red_table[(1 * idx)     * 2 * red_digits], m, k0);
        damm(&red_table[(2 * idx + 1) * 2 * red_digits],
             &red_table[(2 * idx)     * 2 * red_digits],
             &red_table[1 * 2 * red_digits], m, k0);
    }


    memcpy(&expz[0 * (exp_digits + 1)], exp[0], exp_digits * sizeof(BN_ULONG));
    expz[1 * (exp_digits + 1) - 1] = 0;
    memcpy(&expz[1 * (exp_digits + 1)], exp[1], exp_digits * sizeof(BN_ULONG));
    expz[2 * (exp_digits + 1) - 1] = 0;


    {
        const int rem = modulus_bitsize % exp_win_size;
        const BN_ULONG table_idx_mask = exp_win_mask;

        int exp_bit_no = modulus_bitsize - rem;
        int exp_chunk_no = exp_bit_no / 64;
        int exp_chunk_shift = exp_bit_no % 64;

        BN_ULONG red_table_idx_0, red_table_idx_1;


        OPENSSL_assert(rem != 0);


        red_table_idx_0 = expz[exp_chunk_no + 0 * (exp_digits + 1)];
        red_table_idx_1 = expz[exp_chunk_no + 1 * (exp_digits + 1)];


        red_table_idx_0 >>= exp_chunk_shift;
        red_table_idx_1 >>= exp_chunk_shift;

        extract(&red_Y[0 * red_digits], (const BN_ULONG*)red_table, (int)red_table_idx_0, (int)red_table_idx_1);


        for (exp_bit_no -= exp_win_size; exp_bit_no >= 0; exp_bit_no -= exp_win_size) {

            {
                BN_ULONG T;

                exp_chunk_no = exp_bit_no / 64;
                exp_chunk_shift = exp_bit_no % 64;
                {
                    red_table_idx_0 = expz[exp_chunk_no + 0 * (exp_digits + 1)];
                    T = expz[exp_chunk_no + 1 + 0 * (exp_digits + 1)];

                    red_table_idx_0 >>= exp_chunk_shift;


                    if (exp_chunk_shift > 64 - exp_win_size) {
                        T <<= (64 - exp_chunk_shift);
                        red_table_idx_0 ^= T;
                    }
                    red_table_idx_0 &= table_idx_mask;
                }
                {
                    red_table_idx_1 = expz[exp_chunk_no + 1 * (exp_digits + 1)];
                    T = expz[exp_chunk_no + 1 + 1 * (exp_digits + 1)];

                    red_table_idx_1 >>= exp_chunk_shift;


                    if (exp_chunk_shift > 64 - exp_win_size) {
                        T <<= (64 - exp_chunk_shift);
                        red_table_idx_1 ^= T;
                    }
                    red_table_idx_1 &= table_idx_mask;
                }

                extract(&red_X[0 * red_digits], (const BN_ULONG*)red_table, (int)red_table_idx_0, (int)red_table_idx_1);
            }


            DAMS((BN_ULONG*)red_Y, (const BN_ULONG*)red_Y, m, k0);
            DAMS((BN_ULONG*)red_Y, (const BN_ULONG*)red_Y, m, k0);
            DAMS((BN_ULONG*)red_Y, (const BN_ULONG*)red_Y, m, k0);
            DAMS((BN_ULONG*)red_Y, (const BN_ULONG*)red_Y, m, k0);
            DAMS((BN_ULONG*)red_Y, (const BN_ULONG*)red_Y, m, k0);

            damm((BN_ULONG*)red_Y, (const BN_ULONG*)red_Y, (const BN_ULONG*)red_X, m, k0);
        }
    }


    memset(red_X, 0, 2 * red_digits * sizeof(BN_ULONG));
    red_X[0 * red_digits] = 1;
    red_X[1 * red_digits] = 1;
    damm(out, (const BN_ULONG*)red_Y, (const BN_ULONG*)red_X, m, k0);

    ret = 1;

err:
    if (storage != NULL) {

        OPENSSL_cleanse(storage, storage_len_bytes);
        OPENSSL_free(storage);
    }

#undef DAMS
    return ret;
}
