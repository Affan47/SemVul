sustained_level_benchmark(void)
{
    EventQueue *eq;
    Event *e;
    long i;
    long num_deliver;
    long num_submit;
    long rtt;
    long times[MAX_IN_AVERAGE];
    long next_time;
    double time_sum;
    long num_unanswered;

    eq = eq_create();

    httpd_emu_create(eq);
    smsc_emu_create(eq);


    while ((e = eq_extract(eq)) != NULL && e->type != got_smsc)
    	debug("test_smsc", 0, "Discarding event of type %s", eq_type(e));
    debug("test_smsc", 0, "Got event got_smsc.");
    eq_destroy_event(e);


    num_submit = 0;
    for (i = 0; i < MAX_IN_AVERAGE; ++i)
    	times[i] = 0;
    next_time = 0;
    time_sum = 0.0;
    num_unanswered = 0;
    num_deliver = 0;

    while (num_submit < num_messages) {
	for (;;) {
	    if (num_deliver >= num_messages || num_unanswered >= MAX_WAITING)
	    	break;
    	    if (time_sum / MAX_IN_AVERAGE >= MAX_RTT && num_unanswered > 0)
	    	break;
	    smsc_emu_deliver();
	    ++num_unanswered;
	    ++num_deliver;
	}

    	e = eq_extract(eq);
	if (e == NULL)
	    break;
	eq_log(e);

	switch (e->type) {
	case deliver_ack:
	    break;

	case http_request:
	    httpd_emu_reply(e);
	    break;

	case submit:
	    rtt = eq_round_trip_time(e);
	    time_sum -= times[next_time];
	    times[next_time] = rtt;
	    time_sum += times[next_time];
	    debug("", 0, "RTT = %ld", rtt);
	    next_time = (next_time + 1) % MAX_IN_AVERAGE;
	    ++num_submit;
	    --num_unanswered;
	    smsc_emu_submit_ack(e);
	    break;

    	case got_enquire_link:
	    break;

	default:
	    debug("test_smsc", 0, "Ignoring event of type %s", eq_type(e));
	    break;
	}

	eq_destroy_event(e);
    }

    kill_kannel();

    debug("test_smsc", 0, "Terminating benchmark.");
    smsc_emu_destroy();
    httpd_emu_destroy();
    eq_destroy(eq);
}
