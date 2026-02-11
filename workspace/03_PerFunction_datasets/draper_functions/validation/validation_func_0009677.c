reference_free(git_reference *reference)
{
	if (reference == NULL)
		return;

	if (reference->name)
		free(reference->name);

	if (reference->type == GIT_REF_SYMBOLIC)
		free(((reference_symbolic *)reference)->target);

	free(reference);
}
