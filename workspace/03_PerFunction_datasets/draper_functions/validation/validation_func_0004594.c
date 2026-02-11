git_hashsig_compare(const git_hashsig *a, const git_hashsig *b)
{


	if (a->mins.size < HASHSIG_HEAP_SIZE)
		return hashsig_heap_compare(&a->mins, &b->mins);
	else
		return (hashsig_heap_compare(&a->mins, &b->mins) +
				hashsig_heap_compare(&a->maxs, &b->maxs)) / 2;
}
