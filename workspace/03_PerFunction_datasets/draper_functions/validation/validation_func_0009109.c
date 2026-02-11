cnic_submit_kwqe_16(struct cnic_dev *dev, u32 cmd, u32 cid,
				u32 type, union l5cm_specific_data *l5_data)
{
	struct cnic_local *cp = dev->cnic_priv;
	struct bnx2x *bp = netdev_priv(dev->netdev);
	struct l5cm_spe kwqe;
	struct kwqe_16 *kwq[1];
	u16 type_16;
	int ret;

	kwqe.hdr.conn_and_cmd_data =
		cpu_to_le32(((cmd << SPE_HDR_CMD_ID_SHIFT) |
			     BNX2X_HW_CID(bp, cid)));

	type_16 = (type << SPE_HDR_CONN_TYPE_SHIFT) & SPE_HDR_CONN_TYPE;
	type_16 |= (bp->pfid << SPE_HDR_FUNCTION_ID_SHIFT) &
		   SPE_HDR_FUNCTION_ID;

	kwqe.hdr.type = cpu_to_le16(type_16);
	kwqe.hdr.reserved1 = 0;
	kwqe.data.phy_address.lo = cpu_to_le32(l5_data->phy_address.lo);
	kwqe.data.phy_address.hi = cpu_to_le32(l5_data->phy_address.hi);

	kwq[0] = (struct kwqe_16 *) &kwqe;

	spin_lock_bh(&cp->cnic_ulp_lock);
	ret = cp->ethdev->drv_submit_kwqes_16(dev->netdev, kwq, 1);
	spin_unlock_bh(&cp->cnic_ulp_lock);

	if (ret == 1)
		return 0;

	return ret;
}
