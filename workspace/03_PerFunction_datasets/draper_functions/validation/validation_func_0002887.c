memtest(const char *file, int line)
{

	int i;
	void *blocks[MEMTEST_HARDNESS + 1];
	fprintf(stderr,"Memtesting in %s, L%d\n", file, line);

	for (i = 0; i < MEMTEST_HARDNESS; i++) {
		blocks[i] = sci_malloc(1 + i);
#ifdef HAVE_MEMFROB
		memfrob(blocks[i], 1 + i);
#else
		memset(blocks[i], 42, 1 + i);
#endif
	}
	for (i = 0; i < MEMTEST_HARDNESS; i++)
		free(blocks[i]);

	for (i = 0; i < MEMTEST_HARDNESS; i++) {
		blocks[i] = sci_malloc(5 + i*5);
#ifdef HAVE_MEMFROB
		memfrob(blocks[i], 5 + i*5);
#else
		memset(blocks[i], 42, 5 + i*5);
#endif
	}
	for (i = 0; i < MEMTEST_HARDNESS; i++)
		free(blocks[i]);

	for (i = 0; i < MEMTEST_HARDNESS; i++) {
		blocks[i] = sci_malloc(5 + i*100);
#ifdef HAVE_MEMFROB
		memfrob(blocks[i], 5 + i*100);
#else
		memset(blocks[i], 42, 5 + i*100);
#endif
	}
	for (i = 0; i < MEMTEST_HARDNESS; i++)
		free(blocks[i]);

	for (i = 0; i < MEMTEST_HARDNESS; i++) {
		blocks[i] = sci_malloc(5 + i*1000);
#ifdef HAVE_MEMFROB
		memfrob(blocks[i], 5 + i * 1000);
#else
		memset(blocks[i], 42, 5 + i * 1000);
#endif
	}
	for (i = 0; i < MEMTEST_HARDNESS; i++)
		free(blocks[i]);
	fprintf(stderr,"Memtest succeeded!\n");
	return 0;
}
