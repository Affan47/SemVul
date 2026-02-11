parse_remote_refspec(git_config *cfg, git_refspec *refspec, const char *var)
{
	int error;
	const char *val;

	if ((error = git_config_get_string(&val, cfg, var)) < 0)
		return error;

	return refspec_parse(refspec, val);
}
