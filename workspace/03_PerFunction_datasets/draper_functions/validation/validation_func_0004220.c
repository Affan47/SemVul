prism54_process_trap(struct work_struct *work)
{
	struct islpci_mgmtframe *frame =
		container_of(work, struct islpci_mgmtframe, ws);
	struct net_device *ndev = frame->ndev;
	enum oid_num_t n = mgt_oidtonum(frame->header->oid);

	if (n != OID_NUM_LAST)
		prism54_process_trap_helper(netdev_priv(ndev), n, frame->data);
	islpci_mgt_release(frame);
}
