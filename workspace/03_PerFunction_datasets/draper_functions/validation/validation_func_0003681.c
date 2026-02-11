debug_path(struct fuse *f, const char *msg, fuse_ino_t nodeid,
		       const char *name, bool wr)
{
	if (f->conf.debug) {
		struct node *wnode = NULL;

		if (wr)
			wnode = lookup_node(f, nodeid, name);

		if (wnode)
			fprintf(stderr, "%s %li (w)\n",	msg, wnode->nodeid);
		else
			fprintf(stderr, "%s %li\n", msg, nodeid);
	}
}
