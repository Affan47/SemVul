context_create(int fd)
{
	struct local_drm_i915_context_create create;
	int ret;

	ret = drmIoctl(fd, CONTEXT_CREATE_IOCTL, &create);
	if (ret == -1 && (errno == ENODEV || errno == EINVAL))
		exit(77);
	else if (ret)
		abort();

	return create.ctx_id;
}
