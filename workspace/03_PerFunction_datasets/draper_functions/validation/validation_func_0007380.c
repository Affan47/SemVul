BN_STACK_push(BN_STACK *st, unsigned int idx)
	{
	if(st->depth == st->size)

		{
		unsigned int newsize = (st->size ?
				(st->size * 3 / 2) : BN_CTX_START_FRAMES);
		unsigned int *newitems = OPENSSL_malloc(newsize *
						sizeof(unsigned int));
		if(!newitems) return 0;
		if(st->depth)
			memcpy(newitems, st->indexes, st->depth *
						sizeof(unsigned int));
		if(st->size) OPENSSL_free(st->indexes);
		st->indexes = newitems;
		st->size = newsize;
		}
	st->indexes[(st->depth)++] = idx;
	return 1;
	}
