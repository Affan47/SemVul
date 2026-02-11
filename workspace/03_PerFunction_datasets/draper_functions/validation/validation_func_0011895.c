bnx2x_bsc_read(struct link_params *params,
			  struct bnx2x *bp,
			  u8 sl_devid,
			  u16 sl_addr,
			  u8 lc_addr,
			  u8 xfer_cnt,
			  u32 *data_array)
{
	u32 val, i;
	int rc = 0;

	if (xfer_cnt > 16) {
		DP(NETIF_MSG_LINK, "invalid xfer_cnt %d. Max is 16 bytes\n",
					xfer_cnt);
		return -EINVAL;
	}
	bnx2x_bsc_module_sel(params);

	xfer_cnt = 16 - lc_addr;


	val = REG_RD(bp, MCP_REG_MCPR_IMC_COMMAND);
	val |= MCPR_IMC_COMMAND_ENABLE;
	REG_WR(bp, MCP_REG_MCPR_IMC_COMMAND, val);


	val = (sl_devid << 16) | sl_addr;
	REG_WR(bp, MCP_REG_MCPR_IMC_SLAVE_CONTROL, val);


	val = (MCPR_IMC_COMMAND_ENABLE) |
	      (MCPR_IMC_COMMAND_WRITE_OP <<
		MCPR_IMC_COMMAND_OPERATION_BITSHIFT) |
		(lc_addr << MCPR_IMC_COMMAND_TRANSFER_ADDRESS_BITSHIFT) | (0);
	REG_WR(bp, MCP_REG_MCPR_IMC_COMMAND, val);


	i = 0;
	val = REG_RD(bp, MCP_REG_MCPR_IMC_COMMAND);
	while (((val >> MCPR_IMC_COMMAND_IMC_STATUS_BITSHIFT) & 0x3) != 1) {
		udelay(10);
		val = REG_RD(bp, MCP_REG_MCPR_IMC_COMMAND);
		if (i++ > 1000) {
			DP(NETIF_MSG_LINK, "wr 0 byte timed out after %d try\n",
								i);
			rc = -EFAULT;
			break;
		}
	}
	if (rc == -EFAULT)
		return rc;


	val = (MCPR_IMC_COMMAND_ENABLE) |
		(MCPR_IMC_COMMAND_READ_OP <<
		MCPR_IMC_COMMAND_OPERATION_BITSHIFT) |
		(lc_addr << MCPR_IMC_COMMAND_TRANSFER_ADDRESS_BITSHIFT) |
		  (xfer_cnt);
	REG_WR(bp, MCP_REG_MCPR_IMC_COMMAND, val);


	i = 0;
	val = REG_RD(bp, MCP_REG_MCPR_IMC_COMMAND);
	while (((val >> MCPR_IMC_COMMAND_IMC_STATUS_BITSHIFT) & 0x3) != 1) {
		udelay(10);
		val = REG_RD(bp, MCP_REG_MCPR_IMC_COMMAND);
		if (i++ > 1000) {
			DP(NETIF_MSG_LINK, "rd op timed out after %d try\n", i);
			rc = -EFAULT;
			break;
		}
	}
	if (rc == -EFAULT)
		return rc;

	for (i = (lc_addr >> 2); i < 4; i++) {
		data_array[i] = REG_RD(bp, (MCP_REG_MCPR_IMC_DATAREG0 + i*4));
#ifdef __BIG_ENDIAN
		data_array[i] = ((data_array[i] & 0x000000ff) << 24) |
				((data_array[i] & 0x0000ff00) << 8) |
				((data_array[i] & 0x00ff0000) >> 8) |
				((data_array[i] & 0xff000000) >> 24);
#endif
	}
	return rc;
}
