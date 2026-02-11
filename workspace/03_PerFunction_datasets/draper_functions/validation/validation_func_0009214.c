bnx2_init_nvram(struct bnx2 *bp)
{
	u32 val;
	int j, entry_count, rc = 0;
	const struct flash_spec *flash;

	if (BNX2_CHIP(bp) == BNX2_CHIP_5709) {
		bp->flash_info = &flash_5709;
		goto get_flash_size;
	}


	val = BNX2_RD(bp, BNX2_NVM_CFG1);

	entry_count = ARRAY_SIZE(flash_table);

	if (val & 0x40000000) {


		for (j = 0, flash = &flash_table[0]; j < entry_count;
		     j++, flash++) {
			if ((val & FLASH_BACKUP_STRAP_MASK) ==
			    (flash->config1 & FLASH_BACKUP_STRAP_MASK)) {
				bp->flash_info = flash;
				break;
			}
		}
	}
	else {
		u32 mask;


		if (val & (1 << 23))
			mask = FLASH_BACKUP_STRAP_MASK;
		else
			mask = FLASH_STRAP_MASK;

		for (j = 0, flash = &flash_table[0]; j < entry_count;
			j++, flash++) {

			if ((val & mask) == (flash->strapping & mask)) {
				bp->flash_info = flash;


				if ((rc = bnx2_acquire_nvram_lock(bp)) != 0)
					return rc;


				bnx2_enable_nvram_access(bp);


				BNX2_WR(bp, BNX2_NVM_CFG1, flash->config1);
				BNX2_WR(bp, BNX2_NVM_CFG2, flash->config2);
				BNX2_WR(bp, BNX2_NVM_CFG3, flash->config3);
				BNX2_WR(bp, BNX2_NVM_WRITE1, flash->write1);


				bnx2_disable_nvram_access(bp);
				bnx2_release_nvram_lock(bp);

				break;
			}
		}
	}

	if (j == entry_count) {
		bp->flash_info = NULL;
		pr_alert("Unknown flash/EEPROM type\n");
		return -ENODEV;
	}

get_flash_size:
	val = bnx2_shmem_rd(bp, BNX2_SHARED_HW_CFG_CONFIG2);
	val &= BNX2_SHARED_HW_CFG2_NVM_SIZE_MASK;
	if (val)
		bp->flash_size = val;
	else
		bp->flash_size = bp->flash_info->total_size;

	return rc;
}
