static const SIGALG_LOOKUP *find_sig_alg(SSL *s, X509 *x, EVP_PKEY *pkey)
{
    const SIGALG_LOOKUP *lu = NULL;
    size_t i;
#ifndef OPENSSL_NO_EC
    int curve = -1;
#endif
    EVP_PKEY *tmppkey;


    for (i = 0; i < s->shared_sigalgslen; i++) {
        lu = s->shared_sigalgs[i];


        if (lu->hash == NID_sha1
            || lu->hash == NID_sha224
            || lu->sig == EVP_PKEY_DSA
            || lu->sig == EVP_PKEY_RSA)
            continue;

        if (!tls1_lookup_md(s->ctx, lu, NULL))
            continue;
        if ((pkey == NULL && !has_usable_cert(s, lu, -1))
                || (pkey != NULL && !is_cert_usable(s, lu, x, pkey)))
            continue;

        tmppkey = (pkey != NULL) ? pkey
                                 : s->cert->pkeys[lu->sig_idx].privatekey;

        if (lu->sig == EVP_PKEY_EC) {
#ifndef OPENSSL_NO_EC
            if (curve == -1)
                curve = evp_pkey_get_EC_KEY_curve_nid(tmppkey);
            if (lu->curve != NID_undef && curve != lu->curve)
                continue;
#else
            continue;
#endif
        } else if (lu->sig == EVP_PKEY_RSA_PSS) {

            if (!rsa_pss_check_min_key_size(s->ctx, tmppkey, lu))
                continue;
        }
        break;
    }

    if (i == s->shared_sigalgslen)
        return NULL;

    return lu;
}
