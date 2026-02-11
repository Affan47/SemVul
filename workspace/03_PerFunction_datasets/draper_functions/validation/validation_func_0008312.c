_hm_print_heads(const hm_skiplist_t *l){
	hm_skiplist_height_t i;
	for(i = l->height; i > 0; i--)
		printf("\t\t%3u : %12p : %12p\n", i - 1, l->heads[i - 1], l->loc[i - 1]);
}
