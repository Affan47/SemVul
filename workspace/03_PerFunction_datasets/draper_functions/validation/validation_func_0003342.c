sdio_write(u32 addr, u8 *buf, u32 size)
{
	u32 block_size = g_sdio.block_size;
	sdio_cmd53_t cmd;
	int nblk, nleft;

	cmd.read_write = 1;
	if (addr > 0) {


		if (size & 0x3) {
			size += 4;
			size &= ~0x3;
		}


		cmd.function = 0;
		cmd.address = 0x10f;
	} else {


		if (size & 0x3) {
			size += 4;
			size &= ~0x3;
		}


		cmd.function = 1;
		cmd.address = 0;
	}

	nblk = size / block_size;
	nleft = size % block_size;

	if (nblk > 0) {
		cmd.block_mode = 1;
		cmd.increment = 1;
		cmd.count = nblk;
		cmd.buffer = buf;
		cmd.block_size = block_size;
		if (addr > 0) {
			if (!sdio_set_func0_csa_address(addr))
				goto _fail_;
		}
		if (!g_sdio.sdio_cmd53(&cmd)) {
			g_sdio.dPrint(N_ERR, "[wilc sdio]: Failed cmd53 [%x], block send...\n", addr);
			goto _fail_;
		}
		if (addr > 0)
			addr += nblk * block_size;
		buf += nblk * block_size;
	}

	if (nleft > 0) {
		cmd.block_mode = 0;
		cmd.increment = 1;
		cmd.count = nleft;
		cmd.buffer = buf;

		cmd.block_size = block_size;

		if (addr > 0) {
			if (!sdio_set_func0_csa_address(addr))
				goto _fail_;
		}
		if (!g_sdio.sdio_cmd53(&cmd)) {
			g_sdio.dPrint(N_ERR, "[wilc sdio]: Failed cmd53 [%x], bytes send...\n", addr);
			goto _fail_;
		}
	}

	return 1;

_fail_:

	return 0;
}
