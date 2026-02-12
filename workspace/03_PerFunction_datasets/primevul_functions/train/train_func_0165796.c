static void __tun_detach(struct tun_struct *tun)
{

	netif_tx_lock_bh(tun->dev);
	tun->tfile = NULL;
	netif_tx_unlock_bh(tun->dev);


	skb_queue_purge(&tun->readq);


	dev_put(tun->dev);
}
