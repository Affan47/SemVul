nvkm_notify_put(struct nvkm_notify *notify)
{
	struct nvkm_event *event = notify->event;
	unsigned long flags;
	if (likely(event) &&
	    test_and_clear_bit(NVKM_NOTIFY_USER, &notify->flags)) {
		spin_lock_irqsave(&event->refs_lock, flags);
		nvkm_notify_put_locked(notify);
		spin_unlock_irqrestore(&event->refs_lock, flags);
		if (test_bit(NVKM_NOTIFY_WORK, &notify->flags))
			flush_work(&notify->work);
	}
}
