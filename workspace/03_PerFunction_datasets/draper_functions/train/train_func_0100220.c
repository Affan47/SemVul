glfs_first_lookup_safe (xlator_t *subvol)
{
	loc_t  loc = {0, };
	int    ret = -1;

	loc.inode = subvol->itable->root;
	memset (loc.gfid, 0, 16);
	loc.gfid[15] = 1;
	loc.path = "/";
	loc.name = "";

	ret = syncop_lookup (subvol, &loc, 0, 0, 0, 0);

	gf_log (subvol->name, GF_LOG_DEBUG, "first lookup complete %d", ret);

	return ret;
}
