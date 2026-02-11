pr_process(const int bytes, struct sp_xpmsg *req)
{
	struct	joborptr  *pp;
	struct	spptr	inptr;

	if  (bytes != sizeof(struct sp_xpmsg))  {
		disp_arg[9] = bytes;
		report(1110);
	}

	pp = fetch_ptr();
	if  (pp->jorp_sender != req->spr_pid)  {
		nfreport(8120);
		unlockxbuf();
		return;
	}
	BLOCK_COPY(&inptr, &pp->jorp_un.p, sizeof(struct spptr));
	unlockxbuf();

	switch	(req->spr_act)  {
	default:
		disp_arg[9] = req->spr_act;
		report(1108);

	case  SP_ADDP:
		addptr(req, &inptr);
		break;

	case  SP_CHGP:
	case  SP_CHANGEDPTR:
		chgptr(req, &inptr);
		break;

#ifdef	NETWORK_VERSION
	case  SP_PUNASSIGNED:
		unassign_ptr(req, &inptr);
		break;
#endif
	}
}
