static void ep_aio_complete(struct usb_ep *ep, struct usb_request *req)
{
	struct kiocb		*iocb = req->context;
	struct kiocb_priv	*priv = iocb->private;
	struct ep_data		*epdata = priv->epdata;


	spin_lock(&epdata->dev->lock);
	priv->req = NULL;
	priv->epdata = NULL;


	if (priv->to_free == NULL || unlikely(req->actual == 0)) {
		kfree(req->buf);
		kfree(priv->to_free);
		kfree(priv);
		iocb->private = NULL;
		iocb->ki_complete(iocb,
				req->actual ? req->actual : (long)req->status);
	} else {

		if (unlikely(0 != req->status))
			DBG(epdata->dev, "%s fault %d len %d\n",
				ep->name, req->status, req->actual);

		priv->buf = req->buf;
		priv->actual = req->actual;
		INIT_WORK(&priv->work, ep_user_copy_worker);
		schedule_work(&priv->work);
	}

	usb_ep_free_request(ep, req);
	spin_unlock(&epdata->dev->lock);
	put_ep(epdata);
}
