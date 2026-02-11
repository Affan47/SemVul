gitfo_write_cached(gitfo_cache *ioc, void *buff, size_t len)
{
	unsigned char *buf = buff;

	for (;;) {
		size_t space_left = ioc->cache_size - ioc->pos;

		if (space_left > len) {
			gitfo_add_to_cache(ioc, buf, len);
			return GIT_SUCCESS;
		}


		if (ioc->pos) {
			int rc;
			gitfo_add_to_cache(ioc, buf, space_left);
			rc = gitfo_flush_cached(ioc);
			if (rc < 0)
				return rc;

			len -= space_left;
			buf += space_left;
		}


		if (len > ioc->cache_size)
			return gitfo_write(ioc->fd, buf, len);
	}
}
