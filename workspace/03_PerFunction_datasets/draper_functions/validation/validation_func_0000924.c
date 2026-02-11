ccp_resetci(f)
    fsm *f;
{
    ccp_options *go = &ccp_gotoptions[f->unit];
    u_char opt_buf[16];

    *go = ccp_wantoptions[f->unit];
    if (go->bsd_compress) {
	opt_buf[0] = CI_BSD_COMPRESS;
	opt_buf[1] = CILEN_BSD_COMPRESS;
	opt_buf[2] = BSD_MAKE_OPT(BSD_CURRENT_VERSION, go->bsd_bits);
	if (!ccp_test(f->unit, opt_buf, CILEN_BSD_COMPRESS, 0))
	    go->bsd_compress = 0;
    }
}
