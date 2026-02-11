eval_rational_series<false> (uintC N, cl_pqb_series_stream& args, uintC len, uintC trunclen)
{
	if (N==0)
		return cl_I_to_LF(0,len);
	var cl_R Q, B, T;
	eval_pqb_series_aux(0,N,args,NULL,&Q,&B,&T,trunclen);
	return cl_R_to_LF(T,len) / cl_R_to_LF(B*Q,len);
}
