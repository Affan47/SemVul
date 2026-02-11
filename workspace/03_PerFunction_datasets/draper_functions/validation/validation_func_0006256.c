inprec_playevent (int *nr, int *state, int *max, int *autofire)
{
	if (inprec_pstart (INPREC_EVENT)) {
		*nr = inprec_ps16 ();
		*state = inprec_ps16 ();
		*max = inprec_pu16 ();
		*autofire = inprec_ps16 () & 1;
		inprec_pend ();
		return true;
	}
	return false;
}
