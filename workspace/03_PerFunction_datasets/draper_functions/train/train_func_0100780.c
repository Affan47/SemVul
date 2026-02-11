reply_ptradd(const int sock, const struct spdet *priv)
{
	struct	spptr	inptr, rptr;

	pullin(sock, (char *) &inptr, sizeof(inptr));
	swapinp(&rptr, &inptr);
	if  (!(priv->spu_flgs & PV_ADDDEL))  {
		if  (tracing & TRACE_APIOPEND)
			trace_op_res(Realuid, "ptradd", "noperm");
		return  XT_NOPERM;
	}
	if  (rptr.spp_dev[0] == '\0' ||  rptr.spp_ptr[0] == '\0'  ||  rptr.spp_form[0] == '\0')  {
		if  (tracing & TRACE_APIOPEND)
			trace_op_res(Realuid, "ptradd", "nullfield");
		return  XT_PTR_NULL;
	}
	if  (!(priv->spu_flgs & PV_COVER))
		rptr.spp_class &= priv->spu_class;
	if  (rptr.spp_class == 0)  {
		if  (tracing & TRACE_APIOPEND)
			trace_op_res(Realuid, "ptradd", "zerocl");
		return  XT_ZERO_CLASS;
	}
	rptr.spp_netid = 0;
	rptr.spp_minsize = 0;
	rptr.spp_maxsize = 0;
	sp_req.spr_un.p.spr_act = SP_ADDP;
	sp_req.spr_un.p.spr_pid = getpid();
	while  (wpmsg(&sp_req, &rptr) != 0  &&  errno == EAGAIN)
		sleep(SLEEPTIME);
	if  (tracing & TRACE_APIOPEND)
		trace_op_res(Realuid, "ptradd", "OK");
	return  XT_OK;
}
