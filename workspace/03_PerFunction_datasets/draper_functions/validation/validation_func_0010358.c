ccp_down(f)
    fsm *f;
{
    if (ccp_localstate[f->unit] & RACK_PENDING)
	UNTIMEOUT(ccp_rack_timeout, f);
    ccp_localstate[f->unit] = 0;
    ccp_flags_set(f->unit, 1, 0);
#ifdef MPPE
    if (ccp_gotoptions[f->unit].mppe) {
	ccp_gotoptions[f->unit].mppe = 0;
	if (lcp_fsm[f->unit].state == OPENED) {

	    error("MPPE disabled");
	    lcp_close(f->unit, "MPPE disabled");
	}
    }
#endif
}
