static void __vt_event_queue(struct vt_event_wait *vw)
{
	unsigned long flags;

	INIT_LIST_HEAD(&vw->list);
	vw->done = 0;

	spin_lock_irqsave(&vt_event_lock, flags);
	list_add(&vw->list, &vt_events);
	spin_unlock_irqrestore(&vt_event_lock, flags);
}
