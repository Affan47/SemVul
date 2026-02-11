mkiss_close(struct tty_struct *tty)
{
	struct mkiss *ax;

	write_lock_bh(&disc_data_lock);
	ax = tty->disc_data;
	tty->disc_data = NULL;
	write_unlock_bh(&disc_data_lock);

	if (!ax)
		return;


	if (!atomic_dec_and_test(&ax->refcnt))
		down(&ax->dead_sem);


	netif_stop_queue(ax->dev);


	kfree(ax->rbuff);
	kfree(ax->xbuff);

	ax->tty = NULL;

	unregister_netdev(ax->dev);
}
