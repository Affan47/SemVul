videobuf_dvb_start_feed(struct dvb_demux_feed *feed)
{
	struct dvb_demux *demux  = feed->demux;
	struct videobuf_dvb *dvb = demux->priv;
	int rc;

	if (!demux->dmx.frontend)
		return -EINVAL;

	mutex_lock(&dvb->lock);
	dvb->nfeeds++;
	rc = dvb->nfeeds;

	if (NULL != dvb->thread)
		goto out;
	dvb->thread = kthread_run(videobuf_dvb_thread,
				  dvb, "%s dvb", dvb->name);
	if (IS_ERR(dvb->thread)) {
		rc = PTR_ERR(dvb->thread);
		dvb->thread = NULL;
	}

out:
	mutex_unlock(&dvb->lock);
	return rc;
}
