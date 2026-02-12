multi_schedule_context_wakeup(struct multi_context *m, struct multi_instance *mi)
{

    ASSERT(!openvpn_gettimeofday(&mi->wakeup, NULL));
    tv_add(&mi->wakeup, &mi->context.c2.timeval);


    schedule_add_entry(m->schedule,
                       (struct schedule_entry *) mi,
                       &mi->wakeup,
                       compute_wakeup_sigma(&mi->context.c2.timeval));
}
