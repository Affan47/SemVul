handle_env_option(const char *var)
{
	debug((1, "handle_env_option(spec = %s)", var))

	if (g.env == null && !(g.env = list_create(null)))
		fatalsys("failed to create environment list");

	if (!list_append(g.env, (void *)var))
		fatalsys("failed to add '%s' to environment list", var);
}
