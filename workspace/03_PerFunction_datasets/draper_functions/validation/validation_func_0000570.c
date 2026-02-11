cli_bm_free(struct cli_matcher *root)
{
	struct cli_bm_patt *patt, *prev;
	uint16_t i, size = HASH(255, 255, 255) + 1;


    if(root->bm_shift)
	mpool_free(root->mempool, root->bm_shift);

    if(root->bm_pattab)
	mpool_free(root->mempool, root->bm_pattab);

    if(root->bm_suffix) {
	for(i = 0; i < size; i++) {
	    patt = root->bm_suffix[i];
	    while(patt) {
		prev = patt;
		patt = patt->next;
		if(prev->prefix)
		    mpool_free(root->mempool, prev->prefix);
		else
		    mpool_free(root->mempool, prev->pattern);
		if(prev->virname)
		    mpool_free(root->mempool, prev->virname);
		mpool_free(root->mempool, prev);
	    }
	}
	mpool_free(root->mempool, root->bm_suffix);
    }
}
