inode_cksum_invalidate(struct file_opening *fo)
{
	struct inode_open_state *ios = fo->inode->u.c.state;
	struct file_opening *o;

	for (o = ios->openings.opening_next;
	    o != &ios->openings; o = o->opening_next) {
		if (o != fo)
			o->flag |= GFARM_FILE_CKSUM_INVALIDATED;
	}
}
