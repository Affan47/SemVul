scif_invalidate_ep(int node)
{
	struct scif_endpt *ep;
	struct list_head *pos, *tmpq;

	flush_work(&scif_info.conn_work);
	mutex_lock(&scif_info.connlock);
	list_for_each_safe(pos, tmpq, &scif_info.disconnected) {
		ep = list_entry(pos, struct scif_endpt, list);
		if (ep->remote_dev->node == node) {
			scif_unmap_all_windows(ep);
			spin_lock(&ep->lock);
			scif_cleanup_ep_qp(ep);
			spin_unlock(&ep->lock);
		}
	}
	list_for_each_safe(pos, tmpq, &scif_info.connected) {
		ep = list_entry(pos, struct scif_endpt, list);
		if (ep->remote_dev->node == node) {
			list_del(pos);
			spin_lock(&ep->lock);
			ep->state = SCIFEP_DISCONNECTED;
			list_add_tail(&ep->list, &scif_info.disconnected);
			scif_cleanup_ep_qp(ep);
			wake_up_interruptible(&ep->sendwq);
			wake_up_interruptible(&ep->recvwq);
			spin_unlock(&ep->lock);
			scif_unmap_all_windows(ep);
		}
	}
	mutex_unlock(&scif_info.connlock);
}
