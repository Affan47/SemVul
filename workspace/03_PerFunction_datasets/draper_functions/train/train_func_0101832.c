beoboot_probe(const char *buf, off_t len)
{
	struct beoboot_header bb_header;
	const char *cmdline, *kernel;
	int result;
	if ((uintmax_t)len < (uintmax_t)sizeof(bb_header)) {
		return -1;
	}
	memcpy(&bb_header, buf, sizeof(bb_header));
	if (memcmp(bb_header.magic, BEOBOOT_MAGIC, 4) != 0) {
		return -1;
	}
	if (bb_header.arch != BEOBOOT_ARCH) {
		return -1;
	}


	cmdline = buf + sizeof(bb_header);
	kernel  = cmdline + bb_header.cmdline_size;
	result = bzImage_probe(kernel, bb_header.kernel_size);

	return result;
}
