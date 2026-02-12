PJ_DEF(pj_status_t) pjmedia_sdp_media_deactivate(pj_pool_t *pool,
						 pjmedia_sdp_media *m)
{
    PJ_ASSERT_RETURN(m, PJ_EINVAL);
    PJ_UNUSED_ARG(pool);


    m->desc.port = 0;


    m->attr_count = 0;

    return PJ_SUCCESS;
}
