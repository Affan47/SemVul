int RSA_padding_check_SSLv23(unsigned char *to, int tlen,
                             const unsigned char *from, int flen, int num)
{
    int i;

    unsigned char *em = NULL;
    unsigned int good, found_zero_byte, mask, threes_in_row;
    int zero_index = 0, msg_index, mlen = -1, err;

    if (tlen <= 0 || flen <= 0)
        return -1;

    if (flen > num || num < RSA_PKCS1_PADDING_SIZE) {
        RSAerr(RSA_F_RSA_PADDING_CHECK_SSLV23, RSA_R_DATA_TOO_SMALL);
        return -1;
    }

    em = OPENSSL_malloc(num);
    if (em == NULL) {
        RSAerr(RSA_F_RSA_PADDING_CHECK_SSLV23, ERR_R_MALLOC_FAILURE);
        return -1;
    }


    for (from += flen, em += num, i = 0; i < num; i++) {
        mask = ~constant_time_is_zero(flen);
        flen -= 1 & mask;
        from -= 1 & mask;
        *--em = *from & mask;
    }

    good = constant_time_is_zero(em[0]);
    good &= constant_time_eq(em[1], 2);
    err = constant_time_select_int(good, 0, RSA_R_BLOCK_TYPE_IS_NOT_02);
    mask = ~good;


    found_zero_byte = 0;
    threes_in_row = 0;
    for (i = 2; i < num; i++) {
        unsigned int equals0 = constant_time_is_zero(em[i]);

        zero_index = constant_time_select_int(~found_zero_byte & equals0,
                                              i, zero_index);
        found_zero_byte |= equals0;

        threes_in_row += 1 & ~found_zero_byte;
        threes_in_row &= found_zero_byte | constant_time_eq(em[i], 3);
    }


    good &= constant_time_ge(zero_index, 2 + 8);
    err = constant_time_select_int(mask | good, err,
                                   RSA_R_NULL_BEFORE_BLOCK_MISSING);
    mask = ~good;


    good &= constant_time_lt(threes_in_row, 8);
    err = constant_time_select_int(mask | good, err,
                                   RSA_R_SSLV3_ROLLBACK_ATTACK);
    mask = ~good;


    msg_index = zero_index + 1;
    mlen = num - msg_index;


    good &= constant_time_ge(tlen, mlen);
    err = constant_time_select_int(mask | good, err, RSA_R_DATA_TOO_LARGE);


    tlen = constant_time_select_int(constant_time_lt(num - RSA_PKCS1_PADDING_SIZE, tlen),
                                    num - RSA_PKCS1_PADDING_SIZE, tlen);
    for (msg_index = 1; msg_index < num - RSA_PKCS1_PADDING_SIZE; msg_index <<= 1) {
        mask = ~constant_time_eq(msg_index & (num - RSA_PKCS1_PADDING_SIZE - mlen), 0);
        for (i = RSA_PKCS1_PADDING_SIZE; i < num - msg_index; i++)
            em[i] = constant_time_select_8(mask, em[i + msg_index], em[i]);
    }
    for (i = 0; i < tlen; i++) {
        mask = good & constant_time_lt(i, mlen);
        to[i] = constant_time_select_8(mask, em[i + RSA_PKCS1_PADDING_SIZE], to[i]);
    }

    OPENSSL_clear_free(em, num);
    RSAerr(RSA_F_RSA_PADDING_CHECK_SSLV23, err);
    err_clear_last_constant_time(1 & good);

    return constant_time_select_int(good, mlen, -1);
}
