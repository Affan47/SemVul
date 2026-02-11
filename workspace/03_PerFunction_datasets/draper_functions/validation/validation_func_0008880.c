lcp_delayed_up(arg)
    void *arg;
{
    fsm *f = arg;
    FUNC_DEBUG("%s: %d\n", __FUNCTION__,__LINE__);

    if (f->flags & DELAYED_UP) {
	f->flags &= ~DELAYED_UP;
	fsm_lowerup(f);
    }
}
