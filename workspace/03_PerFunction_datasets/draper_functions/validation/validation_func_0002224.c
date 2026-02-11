git_reference__log_signature(git_signature **out, git_repository *repo)
{
	int error;
	git_signature *who;

	if(((error = configured_ident(&who, repo)) < 0) &&
	   ((error = git_signature_default(&who, repo)) < 0) &&
	   ((error = git_signature_now(&who, "unknown", "unknown")) < 0))
		return error;

	*out = who;
	return 0;
}
