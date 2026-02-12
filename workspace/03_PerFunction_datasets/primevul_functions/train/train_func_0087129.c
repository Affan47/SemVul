e1000_mit_timer(void *opaque)
{
    E1000State *s = opaque;

    s->mit_timer_on = 0;

    set_interrupt_cause(s, 0, s->mac_reg[ICR]);
}
