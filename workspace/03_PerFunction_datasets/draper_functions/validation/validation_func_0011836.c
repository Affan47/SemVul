lbtf_cmd_set_mac_multicast_addr(struct lbtf_private *priv)
{
	struct cmd_ds_mac_multicast_addr cmd;

	lbtf_deb_enter(LBTF_DEB_CMD);

	cmd.hdr.size = cpu_to_le16(sizeof(cmd));
	cmd.action = cpu_to_le16(CMD_ACT_SET);

	cmd.nr_of_adrs = cpu_to_le16((u16) priv->nr_of_multicastmacaddr);

	lbtf_deb_cmd("MULTICAST_ADR: setting %d addresses\n", cmd.nr_of_adrs);

	memcpy(cmd.maclist, priv->multicastlist,
	       priv->nr_of_multicastmacaddr * ETH_ALEN);

	lbtf_cmd_async(priv, CMD_MAC_MULTICAST_ADR, &cmd.hdr, sizeof(cmd));

	lbtf_deb_leave(LBTF_DEB_CMD);
	return 0;
}
