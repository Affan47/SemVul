static int cert_crl(X509_STORE_CTX *ctx, X509_CRL *crl, X509 *x)
{
    int idx, ok;
    X509_REVOKED rtmp;
    STACK_OF(X509_EXTENSION) *exts;
    X509_EXTENSION *ext;

    rtmp.serialNumber = X509_get_serialNumber(x);


    if (!sk_X509_REVOKED_is_sorted(crl->crl->revoked)) {
        CRYPTO_w_lock(CRYPTO_LOCK_X509_CRL);
        sk_X509_REVOKED_sort(crl->crl->revoked);
        CRYPTO_w_unlock(CRYPTO_LOCK_X509_CRL);
    }
    idx = sk_X509_REVOKED_find(crl->crl->revoked, &rtmp);


    if (idx >= 0) {
        ctx->error = X509_V_ERR_CERT_REVOKED;
        ok = ctx->verify_cb(0, ctx);
        if (!ok)
            return 0;
    }

    if (ctx->param->flags & X509_V_FLAG_IGNORE_CRITICAL)
        return 1;


    exts = crl->crl->extensions;

    for (idx = 0; idx < sk_X509_EXTENSION_num(exts); idx++) {
        ext = sk_X509_EXTENSION_value(exts, idx);
        if (ext->critical > 0) {
            ctx->error = X509_V_ERR_UNHANDLED_CRITICAL_CRL_EXTENSION;
            ok = ctx->verify_cb(0, ctx);
            if (!ok)
                return 0;
            break;
        }
    }
    return 1;
}
