static int _CheckProbablePrime(mp_int* p, mp_int* q, mp_int* e, int nlen,
                                    int* isPrime, WC_RNG* rng)
{
    int ret;
    mp_int tmp1, tmp2;
    mp_int* prime;

    if (p == NULL || e == NULL || isPrime == NULL)
        return BAD_FUNC_ARG;

    if (!RsaSizeCheck(nlen))
        return BAD_FUNC_ARG;

    *isPrime = MP_NO;

    if (q != NULL) {

        ret = wc_CompareDiffPQ(p, q, nlen);
        if (ret != MP_OKAY) goto notOkay;
        prime = q;
    }
    else
        prime = p;

    ret = mp_init_multi(&tmp1, &tmp2, NULL, NULL, NULL, NULL);
    if (ret != MP_OKAY) goto notOkay;


    ret = mp_read_unsigned_bin(&tmp1, lower_bound, nlen/16);
    if (ret != MP_OKAY) goto notOkay;
    ret = mp_cmp(prime, &tmp1);
    if (ret == MP_LT) goto exit;


    ret = mp_sub_d(prime, 1, &tmp1);
    if (ret != MP_OKAY) goto notOkay;
    ret = mp_gcd(&tmp1, e, &tmp2);
    if (ret != MP_OKAY) goto notOkay;
    ret = mp_cmp_d(&tmp2, 1);
    if (ret != MP_EQ) goto exit;


    if (rng != NULL)
        ret = mp_prime_is_prime_ex(prime, 8, isPrime, rng);
    else
        ret = mp_prime_is_prime(prime, 8, isPrime);
    if (ret != MP_OKAY) goto notOkay;

exit:
    ret = MP_OKAY;
notOkay:
    mp_clear(&tmp1);
    mp_clear(&tmp2);
    return ret;
}
