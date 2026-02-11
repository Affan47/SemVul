myri10ge_change_promisc(struct myri10ge_priv *mgp, int promisc, int atomic)
{
	struct myri10ge_cmd cmd;
	int status, ctl;

	ctl = promisc ? MXGEFW_ENABLE_PROMISC : MXGEFW_DISABLE_PROMISC;
	status = myri10ge_send_cmd(mgp, ctl, &cmd, atomic);
	if (status)
		netdev_err(mgp->dev, "Failed to set promisc mode\n");
}
