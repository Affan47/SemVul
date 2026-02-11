s3fwrn5_fw_get_base_addr(
	struct s3fwrn5_fw_cmd_get_bootinfo_rsp *bootinfo, u32 *base_addr)
{
	int i;
	struct {
		u8 version[4];
		u32 base_addr;
	} match[] = {
		{{0x05, 0x00, 0x00, 0x00}, 0x00005000},
		{{0x05, 0x00, 0x00, 0x01}, 0x00003000},
		{{0x05, 0x00, 0x00, 0x02}, 0x00003000},
		{{0x05, 0x00, 0x00, 0x03}, 0x00003000},
		{{0x05, 0x00, 0x00, 0x05}, 0x00003000}
	};

	for (i = 0; i < ARRAY_SIZE(match); ++i)
		if (bootinfo->hw_version[0] == match[i].version[0] &&
			bootinfo->hw_version[1] == match[i].version[1] &&
			bootinfo->hw_version[3] == match[i].version[3]) {
			*base_addr = match[i].base_addr;
			return 0;
		}

	return -EINVAL;
}
