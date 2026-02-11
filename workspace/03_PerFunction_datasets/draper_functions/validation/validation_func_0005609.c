slow_copy(struct vringh *vrh, void *dst, const void *src,
		     bool (*rcheck)(struct vringh *vrh, u64 addr, size_t *len,
				    struct vringh_range *range,
				    bool (*getrange)(struct vringh *vrh,
						     u64,
						     struct vringh_range *)),
		     bool (*getrange)(struct vringh *vrh,
				      u64 addr,
				      struct vringh_range *r),
		     struct vringh_range *range,
		     int (*copy)(void *dst, const void *src, size_t len))
{
	size_t part, len = sizeof(struct vring_desc);

	do {
		u64 addr;
		int err;

		part = len;
		addr = (u64)(unsigned long)src - range->offset;

		if (!rcheck(vrh, addr, &part, range, getrange))
			return -EINVAL;

		err = copy(dst, src, part);
		if (err)
			return err;

		dst += part;
		src += part;
		len -= part;
	} while (len);
	return 0;
}
