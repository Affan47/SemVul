pp_link_event(void *ctx)
{
	struct pp_ctx *pp = ctx;

	if (ntb_link_is_up(pp->ntb, NULL, NULL) == 1) {
		dev_dbg(&pp->ntb->dev, "link is up\n");
		pp_ping((unsigned long)pp);
	} else {
		dev_dbg(&pp->ntb->dev, "link is down\n");
		del_timer(&pp->db_timer);
	}
}
