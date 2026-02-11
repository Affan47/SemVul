rsi_copy_to_card(struct rsi_common *common,
			    const u8 *fw,
			    u32 len,
			    u32 num_blocks)
{
	struct rsi_hw *adapter = common->priv;
	struct rsi_91x_usbdev *dev = (struct rsi_91x_usbdev *)adapter->rsi_dev;
	u32 indx, ii;
	u32 block_size = dev->tx_blk_size;
	u32 lsb_address;
	u32 base_address;

	base_address = TA_LOAD_ADDRESS;

	for (indx = 0, ii = 0; ii < num_blocks; ii++, indx += block_size) {
		lsb_address = base_address;
		if (rsi_usb_write_register_multiple(adapter,
						    lsb_address,
						    (u8 *)(fw + indx),
						    block_size)) {
			rsi_dbg(ERR_ZONE,
				"%s: Unable to load %s blk\n", __func__,
				FIRMWARE_RSI9113);
			return -EIO;
		}
		rsi_dbg(INIT_ZONE, "%s: loading block: %d\n", __func__, ii);
		base_address += block_size;
	}

	if (len % block_size) {
		lsb_address = base_address;
		if (rsi_usb_write_register_multiple(adapter,
						    lsb_address,
						    (u8 *)(fw + indx),
						    len % block_size)) {
			rsi_dbg(ERR_ZONE,
				"%s: Unable to load %s blk\n", __func__,
				FIRMWARE_RSI9113);
			return -EIO;
		}
	}
	rsi_dbg(INIT_ZONE,
		"%s: Succesfully loaded %s instructions\n", __func__,
		FIRMWARE_RSI9113);

	rsi_dbg(INIT_ZONE, "%s: loaded firmware\n", __func__);
	return 0;
}
