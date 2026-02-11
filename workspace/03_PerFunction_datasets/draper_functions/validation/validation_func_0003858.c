synth_ntom_set_step(long m,long n)
{
	if(param.verbose > 1)
		ast_log(LOG_WARNING,"Init rate converter: %ld->%ld\n",m,n);

	if(n >= 96000 || m >= 96000 || m == 0 || n == 0) {
		ast_log(LOG_WARNING,"NtoM converter: illegal rates\n");
		return (1);
	}

	n *= NTOM_MUL;
	ntom_step = n / m;

	if(ntom_step > 8*NTOM_MUL) {
		ast_log(LOG_WARNING,"max. 1:8 conversion allowed!\n");
		return (1);
	}

	ntom_val[0] = ntom_val[1] = NTOM_MUL>>1;

	return (0);

}
