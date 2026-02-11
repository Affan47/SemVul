pdp_key_open(pdp_ctx_t *ctx, pdp_key_t *key, pdp_key_t *pk,
                 const char *path)
{
    int err = 0;

    if (!ctx || !path) return -1;
    if (key) memset(key, 0, sizeof(pdp_key_t));
    if (pk)  memset(pk, 0, sizeof(pdp_key_t));


    switch(ctx->algo) {
        case PDP_MACPDP:

            PDP_ERR("function not supported for MAC-PDP, yet");
            err = -1;
            break;
        case PDP_APDP:
            err = apdp_key_open(ctx, key, pk, path);
            break;
        case PDP_CPOR:
            err = cpor_key_open(ctx, key, pk, path);
            break;
        case PDP_SEPDP:

            PDP_ERR("function not supported for SE-PDP, yet");
            err = -1;
            break;
        default:
            err = -1;
            break;
    }
    if (err)
        goto cleanup;
    return 0;

cleanup:
    if (key) memset(key, 0, sizeof(pdp_key_t));
    if (pk)  memset(pk, 0, sizeof(pdp_key_t));
    return -1;
}
