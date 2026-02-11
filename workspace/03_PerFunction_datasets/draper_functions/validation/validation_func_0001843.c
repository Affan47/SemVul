lcp_extcode(f, code, id, inp, len)
    fsm *f;
    int code, id;
    u_char *inp;
    int len;
{
    u_char *magp;

    switch( code ){
    case PROTREJ:
	lcp_rprotrej(f, inp, len);
	break;

    case ECHOREQ:
	if (f->state != OPENED)
	    break;
	LCPDEBUG((LOG_INFO, "lcp: Echo-Request, Rcvd id %d", id));
	magp = inp;
	PUTLONG(lcp_gotoptions[f->unit].magicnumber, magp);
	fsm_sdata(f, ECHOREP, id, inp, len);
	break;

    case ECHOREP:
	lcp_received_echo_reply(f, id, inp, len);
	break;

    case DISCREQ:
	break;

    default:
	return 0;
    }
    return 1;
}
