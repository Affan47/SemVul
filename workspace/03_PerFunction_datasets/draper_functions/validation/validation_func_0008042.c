__bdx_vlan_rx_vid(struct net_device *ndev, uint16_t vid, int enable)
{
	struct bdx_priv *priv = netdev_priv(ndev);
	u32 reg, bit, val;

	ENTER;
	DBG2("vid=%d value=%d\n", (int)vid, enable);
	if (unlikely(vid >= 4096)) {
		pr_err("invalid VID: %u (> 4096)\n", vid);
		RET();
	}
	reg = regVLAN_0 + (vid / 32) * 4;
	bit = 1 << vid % 32;
	val = READ_REG(priv, reg);
	DBG2("reg=%x, val=%x, bit=%d\n", reg, val, bit);
	if (enable)
		val |= bit;
	else
		val &= ~bit;
	DBG2("new val %x\n", val);
	WRITE_REG(priv, reg, val);
	RET();
}
