doconnop(const char *hostn)
{
	struct	remote	*rp;
	struct	spr_req	oreq;

	disp_str = hostn;
	while  ((rp = get_hostfile()))
		if  (!(rp->ht_flags & HT_ROAMUSER)  &&  (strcmp(hostn, rp->hostname) == 0  ||  strcmp(hostn, rp->alias) == 0))
			goto  found;
	end_hostfile();
	if  (hostf_errors)
		print_error(8124);
	print_error(176);
	return  E_NOHOST;
 found:

	if  (hostf_errors)
		print_error(8124);


	if  (rp->ht_flags & HT_DOS)  {
		print_error(177);
		return  E_NOHOST;
	}
	oreq.spr_mtype = MT_SCHED;
	oreq.spr_un.n.spr_act = cmd == CONN? SON_CONNECT: SON_DISCONNECT;
	oreq.spr_un.n.spr_seq = 0;
	oreq.spr_un.n.spr_pid = getpid();
	oreq.spr_un.n.spr_n = *rp;
	oreq.spr_un.n.spr_n.ht_flags &= ~HT_MANUAL;
	if  (msgsnd(Ctrl_chan, (struct msgbuf *) &oreq, sizeof(struct sp_nmsg), IPC_NOWAIT) < 0)  {
		print_error(errno == EAGAIN? 8104: 8103);
		exit(E_SETUP);
	}
	return  0;
}
