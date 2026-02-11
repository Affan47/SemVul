init_multi_proc_support(void)
{
	unsigned short proc_no;
	struct socket_info* si;
	#ifdef USE_TCP
	unsigned int i;
	#endif

	proc_no = 0;


	if (dont_fork) {

		proc_no = 1;
	} else {
		#ifdef USE_SCTP

		for (si=sctp_listen; si; si=si->next)
			proc_no+=children_no;
		#endif

		for (si=udp_listen; si; si=si->next)
			proc_no+=children_no;
		#ifdef USE_TCP
		proc_no += ((!tcp_disable)?( 1 + tcp_children_no ):0);
		#endif

		proc_no++;
	}

	proc_no += count_timer_procs();


	proc_no += count_module_procs();


	pt = shm_malloc(sizeof(struct process_table)*proc_no);
	if (pt==0){
		LM_ERR("out of memory\n");
		return -1;
	}
	memset(pt, 0, sizeof(struct process_table)*proc_no);

	#ifdef USE_TCP
	for( i=0 ; i<proc_no ; i++ ) {
		pt[i].unix_sock = -1;
		pt[i].idx = -1;
	}
	#endif


	set_proc_attrs("starter");

	counted_processes = proc_no;

	return 0;
}
