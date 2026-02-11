packbuilder_config(git_packbuilder *pb)
{
	git_config *config;
	int ret;
	int64_t val;

	if (git_repository_config__weakptr(&config, pb->repo) < 0)
		return -1;

#define config_get(KEY,DST,DFLT) do { \
	ret = git_config_get_int64(&val, config, KEY); \
	if (!ret) (DST) = val; \
	else if (ret == GIT_ENOTFOUND) (DST) = (DFLT); \
	else if (ret < 0) return -1; } while (0)

	config_get("pack.deltaCacheSize", pb->max_delta_cache_size,
		   GIT_PACK_DELTA_CACHE_SIZE);
	config_get("pack.deltaCacheLimit", pb->cache_max_small_delta_size,
		   GIT_PACK_DELTA_CACHE_LIMIT);
	config_get("pack.deltaCacheSize", pb->big_file_threshold,
		   GIT_PACK_BIG_FILE_THRESHOLD);
	config_get("pack.windowMemory", pb->window_memory_limit, 0);

#undef config_get

	return 0;
}
