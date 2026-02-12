static void bnx2x_recovery_failed(struct bnx2x *bp)
{
	netdev_err(bp->dev, "Recovery has failed. Power cycle is needed.\n");


	netif_device_detach(bp->dev);


	bnx2x_set_reset_in_progress(bp);


	bnx2x_set_power_state(bp, PCI_D3hot);

	bp->recovery_state = BNX2X_RECOVERY_FAILED;

	smp_mb();
}
