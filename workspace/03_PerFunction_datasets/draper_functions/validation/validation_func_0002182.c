hdestroy(hashp)
	HTAB *hashp;
{
	int32_t save_errno;

	save_errno = 0;

#ifdef HASH_STATISTICS
	{ int i;
	(void)fprintf(stderr, "hdestroy: accesses %ld collisions %ld\n",
	    hash_accesses, hash_collisions);
	(void)fprintf(stderr,
	    "hdestroy: expansions %ld\n", hash_expansions);
	(void)fprintf(stderr,
	    "hdestroy: overflows %ld\n", hash_overflows);
	(void)fprintf(stderr,
	    "hdestroy: big key/data pages %ld\n", hash_bigpages);
	(void)fprintf(stderr,
	    "keys %ld maxp %d\n", hashp->hdr.nkeys, hashp->hdr.max_bucket);

	for (i = 0; i < NCACHED; i++)
		(void)fprintf(stderr,
		    "spares[%d] = %d\n", i, hashp->hdr.spares[i]);
	}
#endif

	if (flush_meta(hashp) && !save_errno)
		save_errno = errno;


	if (hashp->split_buf)
		free(hashp->split_buf);


	if (hashp->bigkey_buf)
		free(hashp->bigkey_buf);
	if (hashp->bigdata_buf)
		free(hashp->bigdata_buf);


	if (hashp->seq_cursor)
		hashp->seq_cursor->delete(NULL, hashp->seq_cursor, 0);


	mpool_sync(hashp->mp);
	mpool_close(hashp->mp);

	if (hashp->fp != -1)
		(void)close(hashp->fp);


	if (hashp->fname && !hashp->save_file) {
#ifdef DEBUG
		fprintf(stderr, "Unlinking file %s.\n", hashp->fname);
#endif

		chmod(hashp->fname, 0700);
		unlink(hashp->fname);

		tmpnam(NULL);
	}
	free(hashp);

	if (save_errno) {
		errno = save_errno;
		return (ERROR);
	}
	return (SUCCESS);
}
