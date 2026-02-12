void llc_restart_tx(struct s_smc *smc)
{
	skfddi_priv *bp = &smc->os;

	PRINTK(KERN_INFO "[llc_restart_tx]\n");


	spin_unlock(&bp->DriverLock);
	send_queued_packets(smc);
	spin_lock(&bp->DriverLock);
	netif_start_queue(bp->dev);

}
