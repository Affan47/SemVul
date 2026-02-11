fs_path_alloc(void)
{
	struct fs_path *p;

	p = kmalloc(sizeof(*p), GFP_NOFS);
	if (!p)
		return NULL;
	p->reversed = 0;
	p->buf = p->inline_buf;
	p->buf_len = FS_PATH_INLINE_SIZE;
	fs_path_reset(p);
	return p;
}
