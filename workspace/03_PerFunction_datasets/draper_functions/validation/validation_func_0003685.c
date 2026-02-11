write_smt_entry(struct adapter *adapter, int idx)
{
	struct cpl_smt_write_req *req;
	struct port_info *pi = netdev_priv(adapter->port[idx]);
	struct sk_buff *skb = alloc_skb(sizeof(*req), GFP_KERNEL);

	if (!skb)
		return -ENOMEM;

	req = (struct cpl_smt_write_req *)__skb_put(skb, sizeof(*req));
	req->wr.wr_hi = htonl(V_WR_OP(FW_WROPCODE_FORWARD));
	OPCODE_TID(req) = htonl(MK_OPCODE_TID(CPL_SMT_WRITE_REQ, idx));
	req->mtu_idx = NMTUS - 1;
	req->iff = idx;
	memcpy(req->src_mac0, adapter->port[idx]->dev_addr, ETH_ALEN);
	memcpy(req->src_mac1, pi->iscsic.mac_addr, ETH_ALEN);
	skb->priority = 1;
	offload_tx(&adapter->tdev, skb);
	return 0;
}
