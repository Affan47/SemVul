put_src_rsc(struct src_mgr *mgr, struct src *src)
{
	unsigned long flags;

	spin_lock_irqsave(&mgr->mgr_lock, flags);
	src->rsc.ops->master(&src->rsc);
	if (MEMRD == src->mode)
		mgr_put_resource(&mgr->mgr, src->multi,
				 src->rsc.ops->index(&src->rsc));
	else
		mgr_put_resource(&mgr->mgr, 1, src->rsc.ops->index(&src->rsc));

	spin_unlock_irqrestore(&mgr->mgr_lock, flags);
	src_rsc_uninit(src, mgr);
	kfree(src);

	return 0;
}
