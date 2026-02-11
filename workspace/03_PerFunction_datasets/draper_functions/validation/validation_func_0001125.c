pack_openidx(git_pack *p)
{
	gitlck_lock(&p->lock);

	if (p->invalid) {
		gitlck_unlock(&p->lock);
		return GIT_ERROR;
	}

	if (++p->idxcnt == 1 && !p->idx_search) {
		int status, version;
		uint32_t *data;

		if (pack_stat(p) || pack_openidx_map(p)) {
			p->invalid = 1;
			p->idxcnt--;
			gitlck_unlock(&p->lock);
			return GIT_ERROR;
		}
		data = p->idx_map.data;
		status = GIT_SUCCESS;
		version = 1;

		if (decode32(&data[0]) == PACK_TOC)
			version = decode32(&data[1]);

		switch (version) {
		case 1:
			status = pack_openidx_v1(p);
			break;
		case 2:
			status = pack_openidx_v2(p);
			break;
		default:
			status = GIT_ERROR;
		}

		if (status != GIT_SUCCESS) {
			gitfo_free_map(&p->idx_map);
			p->invalid = 1;
			p->idxcnt--;
			gitlck_unlock(&p->lock);
			return status;
		}
	}

	gitlck_unlock(&p->lock);
	return GIT_SUCCESS;
}
