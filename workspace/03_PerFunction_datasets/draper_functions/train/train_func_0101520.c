modestack_mode_simple_real(const char *source, channel_t *channel, int dir, int flags)
{
	struct modestackdata *md;

	if (flags == 0)
		return;
	md = modestack_init(source, channel);
	modestack_add_simple(md, dir, flags);
	if (!md->event)
		md->event = event_add_once("flush_cmode_callback", modestack_flush_callback, md, 0);
}
