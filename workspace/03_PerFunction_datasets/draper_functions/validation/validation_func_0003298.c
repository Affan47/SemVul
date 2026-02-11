start_monitor(struct cm4000_dev *dev)
{
	DEBUGP(3, dev, "-> start_monitor\n");
	if (!dev->monitor_running) {
		DEBUGP(5, dev, "create, init and add timer\n");
		setup_timer(&dev->timer, monitor_card, (unsigned long)dev);
		dev->monitor_running = 1;
		mod_timer(&dev->timer, jiffies);
	} else
		DEBUGP(5, dev, "monitor already running\n");
	DEBUGP(3, dev, "<- start_monitor\n");
}
