dns_timer_execute(void)
{
    dns_timer_t *t;
    struct timeval now;

    gettimeofday(&now, NULL);

    while ((t = TimerHead) != NULL) {
        if (timer_tvcompare(&now, &t->t_time) < 0)
            return;

        if ((t->t_flags & TIMER_CONTINUOUS) == 0)
            timer_unregister(t);
        if (t->t_func != NULL)
            t->t_func(t->t_param1, t->t_param2);

        t->t_tocount++;
    }
}
