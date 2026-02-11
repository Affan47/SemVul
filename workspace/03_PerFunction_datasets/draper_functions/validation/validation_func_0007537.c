qlcnic_get_eeprom(struct net_device *dev, struct ethtool_eeprom *eeprom,
		      u8 *bytes)
{
	struct qlcnic_adapter *adapter = netdev_priv(dev);
	int offset;
	int ret = -1;

	if (qlcnic_83xx_check(adapter))
		return 0;
	if (eeprom->len == 0)
		return -EINVAL;

	eeprom->magic = (adapter->pdev)->vendor |
			((adapter->pdev)->device << 16);
	offset = eeprom->offset;

	if (qlcnic_82xx_check(adapter))
		ret = qlcnic_rom_fast_read_words(adapter, offset, bytes,
						 eeprom->len);
	if (ret < 0)
		return ret;

	return 0;
}
