__wa_xfer_delayed_run(struct wa_rpipe *rpipe, int *dto_waiting)
{
	int result, dto_acquired = 0, dto_done = 0;
	struct device *dev = &rpipe->wa->usb_iface->dev;
	struct wa_seg *seg;
	struct wa_xfer *xfer;
	unsigned long flags;

	*dto_waiting = 0;

	spin_lock_irqsave(&rpipe->seg_lock, flags);
	while (atomic_read(&rpipe->segs_available) > 0
	      && !list_empty(&rpipe->seg_list)
	      && (dto_acquired = __wa_dto_try_get(rpipe->wa))) {
		seg = list_first_entry(&(rpipe->seg_list), struct wa_seg,
				 list_node);
		list_del(&seg->list_node);
		xfer = seg->xfer;


		wa_xfer_get(xfer);
		result = __wa_seg_submit(rpipe, xfer, seg, &dto_done);

		if (dto_done)
			__wa_dto_put(rpipe->wa);
		dev_dbg(dev, "xfer %p ID %08X#%u submitted from delayed [%d segments available] %d\n",
			xfer, wa_xfer_id(xfer), seg->index,
			atomic_read(&rpipe->segs_available), result);
		if (unlikely(result < 0)) {
			int done;

			spin_unlock_irqrestore(&rpipe->seg_lock, flags);
			spin_lock_irqsave(&xfer->lock, flags);
			__wa_xfer_abort(xfer);


			xfer->segs_done++;
			done = __wa_xfer_is_done(xfer);
			spin_unlock_irqrestore(&xfer->lock, flags);
			if (done)
				wa_xfer_completion(xfer);
			spin_lock_irqsave(&rpipe->seg_lock, flags);
		}
		wa_xfer_put(xfer);
	}


	if (!dto_acquired && !list_empty(&rpipe->seg_list)
		&& (atomic_read(&rpipe->segs_available) ==
			le16_to_cpu(rpipe->descr.wRequests)))
		*dto_waiting = 1;

	spin_unlock_irqrestore(&rpipe->seg_lock, flags);

	return dto_done;
}
