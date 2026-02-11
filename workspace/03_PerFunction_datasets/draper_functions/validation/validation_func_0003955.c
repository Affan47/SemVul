ecm_unbind(struct usb_configuration *c, struct usb_function *f)
{
	struct f_ecm		*ecm = func_to_ecm(f);

	DBG(c->cdev, "ecm unbind\n");

	usb_free_all_descriptors(f);

	kfree(ecm->notify_req->buf);
	usb_ep_free_request(ecm->notify, ecm->notify_req);
}
