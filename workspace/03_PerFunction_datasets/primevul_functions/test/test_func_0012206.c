static long aspeed_lpc_ctrl_ioctl(struct file *file, unsigned int cmd,
		unsigned long param)
{
	struct aspeed_lpc_ctrl *lpc_ctrl = file_aspeed_lpc_ctrl(file);
	struct device *dev = file->private_data;
	void __user *p = (void __user *)param;
	struct aspeed_lpc_ctrl_mapping map;
	u32 addr;
	u32 size;
	long rc;

	if (copy_from_user(&map, p, sizeof(map)))
		return -EFAULT;

	if (map.flags != 0)
		return -EINVAL;

	switch (cmd) {
	case ASPEED_LPC_CTRL_IOCTL_GET_SIZE:

		if (map.window_type != ASPEED_LPC_CTRL_WINDOW_MEMORY)
			return -EINVAL;


		if (map.window_id != 0)
			return -EINVAL;


		if (!lpc_ctrl->mem_size) {
			dev_dbg(dev, "Didn't find reserved memory\n");
			return -ENXIO;
		}

		map.size = lpc_ctrl->mem_size;

		return copy_to_user(p, &map, sizeof(map)) ? -EFAULT : 0;
	case ASPEED_LPC_CTRL_IOCTL_MAP:


		if ((map.size & 0x0000ffff) || (map.offset & 0x0000ffff))
			return -EINVAL;


		if (map.offset & (map.size - 1))
			return -EINVAL;

		if (map.window_type == ASPEED_LPC_CTRL_WINDOW_FLASH) {
			if (!lpc_ctrl->pnor_size) {
				dev_dbg(dev, "Didn't find host pnor flash\n");
				return -ENXIO;
			}
			addr = lpc_ctrl->pnor_base;
			size = lpc_ctrl->pnor_size;
		} else if (map.window_type == ASPEED_LPC_CTRL_WINDOW_MEMORY) {

			if (!lpc_ctrl->mem_size) {
				dev_dbg(dev, "Didn't find reserved memory\n");
				return -ENXIO;
			}
			addr = lpc_ctrl->mem_base;
			size = lpc_ctrl->mem_size;
		} else {
			return -EINVAL;
		}


		if (map.offset + map.size < map.offset ||
			map.offset + map.size > size)
			return -EINVAL;

		if (map.size == 0 || map.size > size)
			return -EINVAL;

		addr += map.offset;


		rc = regmap_write(lpc_ctrl->regmap, HICR7,
				(addr | (map.addr >> 16)));
		if (rc)
			return rc;

		rc = regmap_write(lpc_ctrl->regmap, HICR8,
				(~(map.size - 1)) | ((map.size >> 16) - 1));
		if (rc)
			return rc;


		if (lpc_ctrl->fwh2ahb)
			regmap_write(lpc_ctrl->regmap, HICR6, SW_FWH2AHB);


		return regmap_update_bits(lpc_ctrl->regmap, HICR5,
				HICR5_ENFWH | HICR5_ENL2H,
				HICR5_ENFWH | HICR5_ENL2H);
	}

	return -EINVAL;
}
