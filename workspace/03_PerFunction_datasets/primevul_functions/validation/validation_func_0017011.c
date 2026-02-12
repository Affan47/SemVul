filter_check_rdns(struct filter *filter, const char *hostname)
{
	int	ret = 0;
	struct netaddr	netaddr;

	if (!filter->config->rdns)
		return 0;


	ret = strcmp("<unknown>", hostname);
	if (ret == 0)
		return filter->config->not_rdns < 0 ? !ret : ret;


	ret = !text_to_netaddr(&netaddr, hostname);
	return filter->config->not_rdns < 0 ? !ret : ret;
}
