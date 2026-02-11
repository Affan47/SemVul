do_write_oneword(struct map_info *map, struct flchip *chip,
				     unsigned long adr, map_word datum, int mode)
{
	struct cfi_private *cfi = map->fldrv_priv;
	map_word status, write_cmd;
	int ret=0;

	adr += chip->start;

	switch (mode) {
	case FL_WRITING:
		write_cmd = (cfi->cfiq->P_ID != P_ID_INTEL_PERFORMANCE) ? CMD(0x40) : CMD(0x41);
		break;
	case FL_OTP_WRITE:
		write_cmd = CMD(0xc0);
		break;
	default:
		return -EINVAL;
	}

	mutex_lock(&chip->mutex);
	ret = get_chip(map, chip, adr, mode);
	if (ret) {
		mutex_unlock(&chip->mutex);
		return ret;
	}

	XIP_INVAL_CACHED_RANGE(map, adr, map_bankwidth(map));
	ENABLE_VPP(map);
	xip_disable(map, chip, adr);
	map_write(map, write_cmd, adr);
	map_write(map, datum, adr);
	chip->state = mode;

	ret = INVAL_CACHE_AND_WAIT(map, chip, adr,
				   adr, map_bankwidth(map),
				   chip->word_write_time,
				   chip->word_write_time_max);
	if (ret) {
		xip_enable(map, chip, adr);
		printk(KERN_ERR "%s: word write error (status timeout)\n", map->name);
		goto out;
	}


	status = map_read(map, adr);
	if (map_word_bitsset(map, status, CMD(0x1a))) {
		unsigned long chipstatus = MERGESTATUS(status);


		map_write(map, CMD(0x50), adr);
		map_write(map, CMD(0x70), adr);
		xip_enable(map, chip, adr);

		if (chipstatus & 0x02) {
			ret = -EROFS;
		} else if (chipstatus & 0x08) {
			printk(KERN_ERR "%s: word write error (bad VPP)\n", map->name);
			ret = -EIO;
		} else {
			printk(KERN_ERR "%s: word write error (status 0x%lx)\n", map->name, chipstatus);
			ret = -EINVAL;
		}

		goto out;
	}

	xip_enable(map, chip, adr);
 out:	DISABLE_VPP(map);
	put_chip(map, chip, adr);
	mutex_unlock(&chip->mutex);
	return ret;
}
