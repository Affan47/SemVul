sepdp_challenge_free(const pdp_ctx_t *ctx, pdp_sepdp_challenge_t *c)
{
    if (!is_sepdp(ctx) || !c)
        return -1;

    if (c->i) c->i = 0;
    sfree(c->ki, c->ki_size);
    sfree(c->ci, c->ci_size);
    memset(c, 0, sizeof(pdp_sepdp_challenge_t));
    return 0;
}
