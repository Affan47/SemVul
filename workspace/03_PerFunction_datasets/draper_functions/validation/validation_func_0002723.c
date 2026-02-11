lbs_mesh_set_txpd(struct lbs_private *priv,
	struct net_device *dev, struct txpd *txpd)
{
	if (dev == priv->mesh_dev) {
		if (priv->mesh_tlv == TLV_TYPE_OLD_MESH_ID)
			txpd->tx_control |= cpu_to_le32(TxPD_MESH_FRAME);
		else if (priv->mesh_tlv == TLV_TYPE_MESH_ID)
			txpd->u.bss.bss_num = MESH_IFACE_ID;
	}
}
