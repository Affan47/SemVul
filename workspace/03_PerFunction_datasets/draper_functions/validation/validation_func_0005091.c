cfs_basic_swrite(int fd, const void *vbuffer, INT64_T length, INT64_T stride_length, INT64_T stride_skip, INT64_T offset)
{
	INT64_T total = 0;
	INT64_T actual = 0;
	const char *buffer = vbuffer;

	if(stride_length < 0 || stride_skip < 0 || offset < 0) {
		errno = EINVAL;
		return -1;
	}

	while(length >= stride_length) {
		actual = cfs->pwrite(fd, &buffer[total], stride_length, offset);
		if(actual > 0) {
			length -= actual;
			total += actual;
			offset += stride_skip;
			if(actual == stride_length) {
				continue;
			} else {
				break;
			}
		} else {
			break;
		}
	}

	if(total > 0) {
		return total;
	} else {
		if(actual < 0) {
			return -1;
		} else {
			return 0;
		}
	}
}
