romfs_checksum(const void *data, int size)
{
	const __be32 *ptr = data;
	__u32 sum;

	sum = 0;
	size >>= 2;
	while (size > 0) {
		sum += be32_to_cpu(*ptr++);
		size--;
	}
	return sum;
}
