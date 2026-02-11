main(int argc, char *argv[])
{
	hash_algorithm_t alg;
	hasher_t *hasher;
	char buffer[1024];
	int limit = 0, i = 0;

	library_init(NULL, "hash_burn");
	lib->plugins->load(lib->plugins, PLUGINS);
	atexit(library_deinit);

	printf("loaded: %s\n", PLUGINS);

	memset(buffer, 0x12, sizeof(buffer));

	if (argc < 2)
	{
		fprintf(stderr, "usage: %s <algorithm>!\n", argv[0]);
		return 1;
	}
	if (argc > 2)
	{
		limit = atoi(argv[2]);
	}

	if (!enum_from_name(hash_algorithm_short_names, argv[1], &alg))
	{
		fprintf(stderr, "unknown hash algorthm: %s\n", argv[1]);
		return 1;
	}
	hasher = lib->crypto->create_hasher(lib->crypto, alg);
	if (!hasher)
	{
		fprintf(stderr, "hash algorthm not supported: %N\n",
				hash_algorithm_names, alg);
		return 1;
	}

	while (TRUE)
	{
		if (!hasher->get_hash(hasher, chunk_from_thing(buffer), buffer))
		{
			fprintf(stderr, "hashing failed!\n");
			return 1;
		}
		if (limit && ++i == limit)
		{
			break;
		}
	}
	hasher->destroy(hasher);
	return 0;
}
