static int slcan_open(struct tty_struct *tty)
{
	struct slcan *sl;
	int err;

	if (!capable(CAP_NET_ADMIN))
		return -EPERM;

	if (tty->ops->write == NULL)
		return -EOPNOTSUPP;


	rtnl_lock();


	slc_sync();

	sl = tty->disc_data;

	err = -EEXIST;

	if (sl && sl->magic == SLCAN_MAGIC)
		goto err_exit;


	err = -ENFILE;
	sl = slc_alloc();
	if (sl == NULL)
		goto err_exit;

	sl->tty = tty;
	tty->disc_data = sl;

	if (!test_bit(SLF_INUSE, &sl->flags)) {

		sl->rcount   = 0;
		sl->xleft    = 0;

		set_bit(SLF_INUSE, &sl->flags);

		err = register_netdevice(sl->dev);
		if (err)
			goto err_free_chan;
	}


	rtnl_unlock();
	tty->receive_room = 65536;


	return 0;

err_free_chan:
	sl->tty = NULL;
	tty->disc_data = NULL;
	clear_bit(SLF_INUSE, &sl->flags);
	slc_free_netdev(sl->dev);

	rtnl_unlock();
	free_netdev(sl->dev);
	return err;

err_exit:
	rtnl_unlock();


	return err;
}
