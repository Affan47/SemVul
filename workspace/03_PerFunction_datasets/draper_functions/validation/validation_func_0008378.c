get_printable_conf(struct ConfItem *aconf, const char **name, const char **host,
		   const char **pass, const char **user, int *port, const char **classname)
{
	static const char *null = "<NULL>";

	*name = EmptyString(aconf->info.name) ? null : aconf->info.name;
	*host = EmptyString(aconf->host) ? null : aconf->host;
	*pass = EmptyString(aconf->passwd) ? null : aconf->passwd;
	*user = EmptyString(aconf->user) ? null : aconf->user;
	*classname = get_class_name(aconf);
	*port = (int)aconf->port;
}
