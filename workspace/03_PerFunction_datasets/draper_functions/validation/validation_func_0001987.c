talloc_autofree(void)
{
	if (autofree_context && *autofree_context == getpid())
		talloc_free(autofree_context);
}
