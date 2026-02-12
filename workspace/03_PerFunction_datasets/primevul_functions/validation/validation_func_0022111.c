static int ecdsa_sign_setup(EC_KEY *eckey, BN_CTX *ctx_in,
                            BIGNUM **kinvp, BIGNUM **rp,
                            const unsigned char *dgst, int dlen)
{
    BN_CTX *ctx = NULL;
    BIGNUM *k = NULL, *r = NULL, *X = NULL;
    const BIGNUM *order;
    EC_POINT *tmp_point = NULL;
    const EC_GROUP *group;
    int ret = 0;
    int order_bits;

    if (eckey == NULL || (group = EC_KEY_get0_group(eckey)) == NULL) {
        ECerr(EC_F_ECDSA_SIGN_SETUP, ERR_R_PASSED_NULL_PARAMETER);
        return 0;
    }

    if (!EC_KEY_can_sign(eckey)) {
        ECerr(EC_F_ECDSA_SIGN_SETUP, EC_R_CURVE_DOES_NOT_SUPPORT_SIGNING);
        return 0;
    }

    if (ctx_in == NULL) {
        if ((ctx = BN_CTX_new()) == NULL) {
            ECerr(EC_F_ECDSA_SIGN_SETUP, ERR_R_MALLOC_FAILURE);
            return 0;
        }
    } else
        ctx = ctx_in;

    k = BN_new();
    r = BN_new();
    X = BN_new();
    if (k == NULL || r == NULL || X == NULL) {
        ECerr(EC_F_ECDSA_SIGN_SETUP, ERR_R_MALLOC_FAILURE);
        goto err;
    }
    if ((tmp_point = EC_POINT_new(group)) == NULL) {
        ECerr(EC_F_ECDSA_SIGN_SETUP, ERR_R_EC_LIB);
        goto err;
    }
    order = EC_GROUP_get0_order(group);
    if (order == NULL) {
        ECerr(EC_F_ECDSA_SIGN_SETUP, ERR_R_EC_LIB);
        goto err;
    }


    order_bits = BN_num_bits(order);
    if (!BN_set_bit(k, order_bits)
        || !BN_set_bit(r, order_bits)
        || !BN_set_bit(X, order_bits))
        goto err;

    do {

        do
            if (dgst != NULL) {
                if (!BN_generate_dsa_nonce
                    (k, order, EC_KEY_get0_private_key(eckey), dgst, dlen,
                     ctx)) {
                    ECerr(EC_F_ECDSA_SIGN_SETUP,
                             EC_R_RANDOM_NUMBER_GENERATION_FAILED);
                    goto err;
                }
            } else {
                if (!BN_rand_range(k, order)) {
                    ECerr(EC_F_ECDSA_SIGN_SETUP,
                             EC_R_RANDOM_NUMBER_GENERATION_FAILED);
                    goto err;
                }
            }
        while (BN_is_zero(k));


        if (!BN_add(r, k, order)
            || !BN_add(X, r, order)
            || !BN_copy(k, BN_num_bits(r) > order_bits ? r : X))
            goto err;


        if (!EC_POINT_mul(group, tmp_point, k, NULL, NULL, ctx)) {
            ECerr(EC_F_ECDSA_SIGN_SETUP, ERR_R_EC_LIB);
            goto err;
        }
        if (EC_METHOD_get_field_type(EC_GROUP_method_of(group)) ==
            NID_X9_62_prime_field) {
            if (!EC_POINT_get_affine_coordinates_GFp
                (group, tmp_point, X, NULL, ctx)) {
                ECerr(EC_F_ECDSA_SIGN_SETUP, ERR_R_EC_LIB);
                goto err;
            }
        }
#ifndef OPENSSL_NO_EC2M
        else {

            if (!EC_POINT_get_affine_coordinates_GF2m(group,
                                                      tmp_point, X, NULL,
                                                      ctx)) {
                ECerr(EC_F_ECDSA_SIGN_SETUP, ERR_R_EC_LIB);
                goto err;
            }
        }
#endif
        if (!BN_nnmod(r, X, order, ctx)) {
            ECerr(EC_F_ECDSA_SIGN_SETUP, ERR_R_BN_LIB);
            goto err;
        }
    }
    while (BN_is_zero(r));


    if (EC_GROUP_get_mont_data(group) != NULL) {


        if (!BN_set_word(X, 2)) {
            ECerr(EC_F_ECDSA_SIGN_SETUP, ERR_R_BN_LIB);
            goto err;
        }
        if (!BN_mod_sub(X, order, X, order, ctx)) {
            ECerr(EC_F_ECDSA_SIGN_SETUP, ERR_R_BN_LIB);
            goto err;
        }
        BN_set_flags(X, BN_FLG_CONSTTIME);
        if (!BN_mod_exp_mont_consttime
            (k, k, X, order, ctx, EC_GROUP_get_mont_data(group))) {
            ECerr(EC_F_ECDSA_SIGN_SETUP, ERR_R_BN_LIB);
            goto err;
        }
    } else {
        if (!BN_mod_inverse(k, k, order, ctx)) {
            ECerr(EC_F_ECDSA_SIGN_SETUP, ERR_R_BN_LIB);
            goto err;
        }
    }


    BN_clear_free(*rp);
    BN_clear_free(*kinvp);

    *rp = r;
    *kinvp = k;
    ret = 1;
 err:
    if (!ret) {
        BN_clear_free(k);
        BN_clear_free(r);
    }
    if (ctx != ctx_in)
        BN_CTX_free(ctx);
    EC_POINT_free(tmp_point);
    BN_clear_free(X);
    return (ret);
}
