md_init_ctx( md_context_t *ctx, const md_info_t *md_info )
{
    if( md_info == NULL || ctx == NULL )
        return POLARSSL_ERR_MD_BAD_INPUT_DATA;

    memset( ctx, 0, sizeof( md_context_t ) );

    if( ( ctx->md_ctx = md_info->ctx_alloc_func() ) == NULL )
        return POLARSSL_ERR_MD_ALLOC_FAILED;

    ctx->md_info = md_info;

    md_info->starts_func( ctx->md_ctx );

    return 0;
}
