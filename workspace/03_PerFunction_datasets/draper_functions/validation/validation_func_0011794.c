config_parse_zone_search_engine_param(dns_config_zone_search_t *search, config_context_t *ctx, dns_engine_t *engine, dns_config_zone_t *zone, void *econf)
{
    config_token_t tok;

    if (config_get_token(&tok, ctx) < 0) {
        config_error_eof(ctx);
        return -1;
    }

    if (tok.tok_code != CONFIG_TOKEN_STRING) {
        config_unget_token(&tok, ctx);
        return 0;
    }

    if (dns_engine_setarg(engine, zone, econf, tok.tok_string) < 0) {
        config_error("invalid parameter", &tok, ctx);
        return -1;
    }

    return 0;
}
