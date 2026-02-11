clients_free(RADCLIENT_LIST *clients)
{
	int i;

	if (!clients) return;

	for (i = 0; i <= 128; i++) {
		if (clients->trees[i]) rbtree_free(clients->trees[i]);
		clients->trees[i] = NULL;
	}

	if (clients == root_clients) {
#ifdef WITH_STATS
		if (tree_num) rbtree_free(tree_num);
		tree_num = NULL;
		tree_num_max = 0;
#endif
		root_clients = NULL;
	}

#ifdef WITH_DYNAMIC_CLIENTS


#endif

	free(clients);
}
