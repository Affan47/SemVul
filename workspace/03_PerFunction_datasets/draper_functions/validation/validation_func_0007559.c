verify_clean_subdirectory(struct cache_entry *ce, const char *action,
				      struct unpack_trees_options *o)
{


	int namelen;
	int pos, i;
	struct dir_struct d;
	char *pathbuf;
	int cnt = 0;
	unsigned char sha1[20];

	if (S_ISGITLINK(ce->ce_mode) &&
	    resolve_gitlink_ref(ce->name, "HEAD", sha1) == 0) {


		if (!hashcmp(sha1, ce->sha1))
			return 0;
		return verify_clean_submodule(ce, action, o);
	}


	namelen = strlen(ce->name);
	pos = index_name_pos(o->src_index, ce->name, namelen);
	if (0 <= pos)
		return cnt;
	pos = -pos - 1;
	for (i = pos; i < o->src_index->cache_nr; i++) {
		struct cache_entry *ce = o->src_index->cache[i];
		int len = ce_namelen(ce);
		if (len < namelen ||
		    strncmp(ce->name, ce->name, namelen) ||
		    ce->name[namelen] != '/')
			break;


		if (!ce_stage(ce)) {
			if (verify_uptodate(ce, o))
				return -1;
			add_entry(o, ce, CE_REMOVE, 0);
		}
		cnt++;
	}


	pathbuf = xmalloc(namelen + 2);
	memcpy(pathbuf, ce->name, namelen);
	strcpy(pathbuf+namelen, "/");

	memset(&d, 0, sizeof(d));
	if (o->dir)
		d.exclude_per_dir = o->dir->exclude_per_dir;
	i = read_directory(&d, ce->name, pathbuf, namelen+1, NULL);
	if (i)
		return o->gently ? -1 :
			error(ERRORMSG(o, not_uptodate_dir), ce->name);
	free(pathbuf);
	return cnt;
}
