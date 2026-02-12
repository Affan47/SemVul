PJ_DEF(void) pj_cis_invert( pj_cis_t *cis )
{
    unsigned i;

    for (i=1; i<256; ++i) {
	if (PJ_CIS_ISSET(cis,i))
            PJ_CIS_CLR(cis,i);
        else
            PJ_CIS_SET(cis,i);
    }
}
