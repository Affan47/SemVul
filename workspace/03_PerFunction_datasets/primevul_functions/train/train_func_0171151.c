static int test_rand(void)
{
    BIGNUM *bn = NULL;
    int st = 0;

    if (!TEST_ptr(bn = BN_new()))
        return 0;


    if (!TEST_false(BN_rand(bn, 0, 0  , 0  ))
            || !TEST_false(BN_rand(bn, 0, 1  , 1  ))
            || !TEST_true(BN_rand(bn, 1, 0  , 0  ))
            || !TEST_BN_eq_one(bn)
            || !TEST_false(BN_rand(bn, 1, 1  , 0  ))
            || !TEST_true(BN_rand(bn, 1, -1  , 1  ))
            || !TEST_BN_eq_one(bn)
            || !TEST_true(BN_rand(bn, 2, 1  , 0  ))
            || !TEST_BN_eq_word(bn, 3))
        goto err;

    st = 1;
 err:
    BN_free(bn);
    return st;
}
