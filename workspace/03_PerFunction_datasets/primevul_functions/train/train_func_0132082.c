static int initialize_module(apr_pool_t *p, apr_pool_t *plog,
                             apr_pool_t *ptemp, server_rec *s)
{


    if (ap_state_query(AP_SQ_MAIN_STATE) == AP_SQ_MS_CREATE_PRE_CONFIG)
        return OK;

#if APR_HAS_SHARED_MEMORY


    if (initialize_tables(s, p) != OK) {
        return !OK;
    }
#endif
    return OK;
}
