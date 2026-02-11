chirp_global_stat(const char *host, const char *path, struct chirp_stat * buf, time_t stoptime)
{
	if(is_multi_path(host)) {
		char mhost[CHIRP_PATH_MAX];
		char mpath[CHIRP_PATH_MAX];
		parse_multi_path(path, mhost, mpath);
		return chirp_multi_stat(mhost, mpath, buf, stoptime);
	} else if(not_empty(path)) {
		return chirp_reli_stat(host, path, buf, stoptime);
	} else if(not_empty(host)) {
		struct nvpair *nv = server_lookup(host, stoptime);
		if(nv) {
			chirp_nvpair_to_stat(nv, buf);
			return 0;
		} else {
			return chirp_reli_stat(host, "/", buf, stoptime);
		}
	} else {
		chirp_blank_stat(buf);
		return 0;
	}
}
