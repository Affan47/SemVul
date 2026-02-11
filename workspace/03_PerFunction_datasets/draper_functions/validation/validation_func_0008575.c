irtty_close(struct tty_struct *tty)
{
	struct sirtty_cb *priv = tty->disc_data;

	IRDA_ASSERT(priv != NULL, return;);
	IRDA_ASSERT(priv->magic == IRTTY_MAGIC, return;);


	tty->disc_data = NULL;

	sirdev_put_instance(priv->dev);


	clear_bit(TTY_DO_WRITE_WAKEUP, &tty->flags);
	if (tty->ops->stop)
		tty->ops->stop(tty);

	kfree(priv);

	pr_debug("%s - %s: irda line discipline closed\n", __func__, tty->name);
}
