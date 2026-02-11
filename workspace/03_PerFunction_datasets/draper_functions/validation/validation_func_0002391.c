fsm_rconfreq(f, id, inp, len)
    fsm *f;
    u_char id;
    u_char *inp;
    int len;
{
    u_char *outp;
    int code, reject_if_disagree;

    FSMDEBUG((LOG_INFO, "fsm_rconfreq(%s): Rcvd id %d.", PROTO_NAME(f), id));
    switch( f->state ){
    case CLOSED:

	fsm_sdata(f, TERMACK, id, NULL, 0);
	return;
    case CLOSING:
    case STOPPING:
	return;

    case OPENED:

	if( f->callbacks->down )
	    (*f->callbacks->down)(f);
	fsm_sconfreq(f, 0);
	break;

    case STOPPED:

	fsm_sconfreq(f, 0);
	f->state = REQSENT;
	break;
    }


    if (f->callbacks->reqci){
	reject_if_disagree = (f->nakloops >= f->maxnakloops);
	code = (*f->callbacks->reqci)(f, inp, &len, reject_if_disagree);
    } else if (len)
	code = CONFREJ;
    else
	code = CONFACK;


    fsm_sdata(f, code, id, inp, len);

    if (code == CONFACK) {
	if (f->state == ACKRCVD) {
	    UNTIMEOUT(fsm_timeout, (caddr_t) f);
	    f->state = OPENED;
	    if (f->callbacks->up)
		(*f->callbacks->up)(f);
	} else
	    f->state = ACKSENT;
	f->nakloops = 0;

    } else {

	if (f->state != ACKRCVD)
	    f->state = REQSENT;
	if( code == CONFNAK )
	    ++f->nakloops;
    }
}
