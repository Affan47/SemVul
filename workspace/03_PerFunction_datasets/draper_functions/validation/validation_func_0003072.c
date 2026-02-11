pn533_listen_mode_timer(unsigned long data)
{
	struct pn533 *dev = (struct pn533 *)data;

	dev_dbg(&dev->interface->dev, "Listen mode timeout\n");

	dev->cancel_listen = 1;

	pn533_poll_next_mod(dev);

	queue_delayed_work(dev->wq, &dev->poll_work,
			   msecs_to_jiffies(PN533_POLL_INTERVAL));
}
