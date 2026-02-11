ref_gather_orphans(const char *key __attribute__((unused)),
			       void *data, void *rock)
{
    Thread *node = (Thread *)data;
    struct rootset *rootset = (struct rootset *)rock;


    if (!node->parent) {
	if (node->next) {


	    return;
	}


	node->next = rootset->root->child;
	rootset->root->child = node;
	rootset->nroot++;
    }
}
