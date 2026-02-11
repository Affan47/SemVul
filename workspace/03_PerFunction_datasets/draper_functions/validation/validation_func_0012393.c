interpolated_freq(int k, SPN *ps)
{
	int i;
	int freq;

	if(!ps->t_sz)
	    return(DEF_F0);
	else if(k<ps->abs_targ[0])
	    return(ps->targ_freq[0]);
	else if(k>=ps->abs_targ[ps->t_sz-1])
	    return(ps->targ_freq[ps->t_sz-1]);
	for(i=1;i<ps->t_sz;i++) {
	    if((k<ps->abs_targ[i]) && (k>=ps->abs_targ[i-1]))
	    {
		freq = interpolate(ps->abs_targ[i-1],
				   ps->targ_freq[i-1],
				   ps->abs_targ[i],
				   ps->targ_freq[i],k);
		return(freq);
	    }
	}
	return(-1);
}
