run_kernel(int argc, char* argv[])
{
	struct kproc	*pclient;
	struct kproc	*pnext;
	struct kreq	*pkq;
	struct kreq	request;
	int		go = 1;
	int		i;


	kio_init();


	for (i = 0; i < KPMAX; ++i) {
		procs[i].kp_index = i;
		procs[i].kp_state = KSFREE;
		procs[i].kp_next = procs + (i + 1);
	}

	procs[KPMAX - 1].kp_next = 0;
	pfree = procs;
	pready = 0;


	kboot(&argc, argv);

	lamlog("kernel:  initialized\n");

	while (go) {


	    prun = pready;

	    while (prun) {
		pnext = prun->kp_next;

		if (prun->kp_flags & KIPROC) {

		    if (aq_count(prun->kp_kqueue) <= 0) {
			prun->kp_run = (void (*((*)()))())
				(*prun->kp_run)(argc, argv);
		    }

		    if (aq_count(prun->kp_kqueue) > 0) {
			memcpy((char *) &request,
				(char *) aq_find(prun->kp_kqueue),
				sizeof(struct kreq));
			aq_delete(prun->kp_kqueue);

			if (request.kq_req == KQDETACH) {
			    kqdetach(&request);
			} else {
			    (*kq[request.kq_req])(prun, &request);
			    pnext = pready;
			}
		    }
		}

		prun = pnext;
	    }


	    if (! (pkq = kio_req())) {
		continue;
	    }


	    if (pkq->kq_req == KQDETACH) {
		kqdetach(pkq);
	    } else if ((pkq->kq_req == KQATTACH) && (pkq->kq_index == -1)) {
		kqattach((struct kproc *) 0, pkq);
	    } else if (pkq->kq_req == KQDUMP) {
		kqdump();
	    } else {


		if ((pkq->kq_req < 0) || (pkq->kq_req >= KQMAX))
		    continue;
		if ((pkq->kq_index < 0) || (pkq->kq_index >= KPMAX))
		    continue;

		pclient = procs + pkq->kq_index;
		prun = pclient;
		(*kq[pkq->kq_req])(pclient, pkq);
	    }
	}

	return(0);
}
