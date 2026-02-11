stats_set_refresh(struct uri_auth **root, int interval)
{
	struct uri_auth *u;

	if ((u = stats_check_init_uri_auth(root)) != NULL)
		u->refresh = interval;
	return u;
}
