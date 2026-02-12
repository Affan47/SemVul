static void RSAZ_exp52x20_x2_256(BN_ULONG *out,
                                 const BN_ULONG *base,
                                 const BN_ULONG *exp[2],
                                 const BN_ULONG *m,
                                 const BN_ULONG *rr,
                                 const BN_ULONG k0[2])
{
# define BITSIZE_MODULUS (1024)
# define EXP_WIN_SIZE (5)
# define EXP_WIN_MASK ((1U << EXP_WIN_SIZE) - 1)


# define RED_DIGITS (20)
# define EXP_DIGITS (16)
# define DAMM ossl_rsaz_amm52x20_x2_256


# define DAMS(r,a,m,k0) \
              ossl_rsaz_amm52x20_x2_256((r),(a),(a),(m),(k0))


    ALIGN64 BN_ULONG red_Y[2][RED_DIGITS];
    ALIGN64 BN_ULONG red_X[2][RED_DIGITS];


    ALIGN64 BN_ULONG expz[2][EXP_DIGITS + 1];


    ALIGN64 BN_ULONG red_table[1U << EXP_WIN_SIZE][2][RED_DIGITS];

    int idx;

    memset(red_Y, 0, sizeof(red_Y));
    memset(red_table, 0, sizeof(red_table));
    memset(red_X, 0, sizeof(red_X));


    red_X[0][0] = 1;
    red_X[1][0] = 1;
    DAMM(red_table[0][0], (const BN_ULONG*)red_X, rr, m, k0);
    DAMM(red_table[1][0], base,  rr, m, k0);

    for (idx = 1; idx < (int)((1U << EXP_WIN_SIZE) / 2); idx++) {
        DAMS(red_table[2 * idx + 0][0], red_table[1 * idx][0], m, k0);
        DAMM(red_table[2 * idx + 1][0], red_table[2 * idx][0], red_table[1][0], m, k0);
    }


    memcpy(expz[0], exp[0], EXP_DIGITS * sizeof(BN_ULONG));
    expz[0][EXP_DIGITS] = 0;
    memcpy(expz[1], exp[1], EXP_DIGITS * sizeof(BN_ULONG));
    expz[1][EXP_DIGITS] = 0;


    {
        const int rem = BITSIZE_MODULUS % EXP_WIN_SIZE;
        BN_ULONG table_idx_mask = EXP_WIN_MASK;

        int exp_bit_no = BITSIZE_MODULUS - rem;
        int exp_chunk_no = exp_bit_no / 64;
        int exp_chunk_shift = exp_bit_no % 64;

        BN_ULONG red_table_idx_0, red_table_idx_1;


        OPENSSL_assert(rem != 0);


        red_table_idx_0 = expz[0][exp_chunk_no];
        red_table_idx_1 = expz[1][exp_chunk_no];


        red_table_idx_0 >>= exp_chunk_shift;
        red_table_idx_1 >>= exp_chunk_shift;

        ossl_extract_multiplier_2x20_win5(red_Y[0], (const BN_ULONG*)red_table,
                                          (int)red_table_idx_0, 0);
        ossl_extract_multiplier_2x20_win5(red_Y[1], (const BN_ULONG*)red_table,
                                          (int)red_table_idx_1, 1);


        for (exp_bit_no -= EXP_WIN_SIZE; exp_bit_no >= 0; exp_bit_no -= EXP_WIN_SIZE) {

            {
                BN_ULONG T;

                exp_chunk_no = exp_bit_no / 64;
                exp_chunk_shift = exp_bit_no % 64;
                {
                    red_table_idx_0 = expz[0][exp_chunk_no];
                    T = expz[0][exp_chunk_no + 1];

                    red_table_idx_0 >>= exp_chunk_shift;


                    if (exp_chunk_shift > 64 - EXP_WIN_SIZE) {
                        T <<= (64 - exp_chunk_shift);
                        red_table_idx_0 ^= T;
                    }
                    red_table_idx_0 &= table_idx_mask;

                    ossl_extract_multiplier_2x20_win5(red_X[0],
                                                      (const BN_ULONG*)red_table,
                                                      (int)red_table_idx_0, 0);
                }
                {
                    red_table_idx_1 = expz[1][exp_chunk_no];
                    T = expz[1][exp_chunk_no + 1];

                    red_table_idx_1 >>= exp_chunk_shift;


                    if (exp_chunk_shift > 64 - EXP_WIN_SIZE) {
                        T <<= (64 - exp_chunk_shift);
                        red_table_idx_1 ^= T;
                    }
                    red_table_idx_1 &= table_idx_mask;

                    ossl_extract_multiplier_2x20_win5(red_X[1],
                                                      (const BN_ULONG*)red_table,
                                                      (int)red_table_idx_1, 1);
                }
            }


            DAMS((BN_ULONG*)red_Y, (const BN_ULONG*)red_Y, m, k0);
            DAMS((BN_ULONG*)red_Y, (const BN_ULONG*)red_Y, m, k0);
            DAMS((BN_ULONG*)red_Y, (const BN_ULONG*)red_Y, m, k0);
            DAMS((BN_ULONG*)red_Y, (const BN_ULONG*)red_Y, m, k0);
            DAMS((BN_ULONG*)red_Y, (const BN_ULONG*)red_Y, m, k0);

            DAMM((BN_ULONG*)red_Y, (const BN_ULONG*)red_Y, (const BN_ULONG*)red_X, m, k0);
        }
    }


    memset(red_X, 0, sizeof(red_X));
    red_X[0][0] = 1;
    red_X[1][0] = 1;
    DAMM(out, (const BN_ULONG*)red_Y, (const BN_ULONG*)red_X, m, k0);


    OPENSSL_cleanse(expz, sizeof(expz));
    OPENSSL_cleanse(red_Y, sizeof(red_Y));

# undef DAMS
# undef DAMM
# undef EXP_DIGITS
# undef RED_DIGITS
# undef EXP_WIN_MASK
# undef EXP_WIN_SIZE
# undef BITSIZE_MODULUS
}
