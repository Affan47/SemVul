invalidate_webkdc_factors(struct webauth_context *ctx,
                          apr_array_header_t *wkfactors,
                          time_t valid_threshold)
{
    bool invalidated = false;
    time_t now;
    int i;


    if (valid_threshold == 0)
        return false;
    if (apr_is_empty_array(wkfactors))
        return false;


    now = time(NULL);
    for (i = 0; i < wkfactors->nelts; i++) {
        struct webauth_token *token;
        struct webauth_token_webkdc_factor *wft;


        token = APR_ARRAY_IDX(wkfactors, i, struct webauth_token *);
        if (token->type != WA_TOKEN_WEBKDC_FACTOR)
            continue;
        wft = &token->token.webkdc_factor;


        if (wft->creation < valid_threshold) {
            wai_log_notice(ctx, "invalidating webkdc-factor token for %s"
                           " (creation %lu < %lu)", wft->subject,
                           (unsigned long) wft->creation,
                           (unsigned long) valid_threshold);
            wft->expiration = now - 1;
            invalidated = true;
        }
    }
    return invalidated;
}
