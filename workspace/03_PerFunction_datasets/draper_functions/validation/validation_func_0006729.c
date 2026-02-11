set_virtual_timer(unsigned seconds, Timer_Proc proc, Timer_Data data)
{
#ifdef ITIMER_VIRTUAL

    if (virtual_timer)
	return -1;

    stop_timers();

    virtual_timer = allocate_timer();
    virtual_timer->id = next_id++;
    virtual_timer->when = seconds;
    virtual_timer->proc = proc;
    virtual_timer->data = data;

    restart_timers();

    return virtual_timer->id;

#else

    return set_timer(seconds, proc, data);

#endif
}
