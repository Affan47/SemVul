isdn_net_newslave(char *parm)
{
	char *p = strchr(parm, ',');
	isdn_net_dev *n;
	char newname[10];

	if (p) {

		if (strscpy(newname, p + 1, sizeof(newname)) <= 0)
			return NULL;
		*p = 0;

		if (!(n = isdn_net_findif(parm)))
			return NULL;

		if (n->local->master)
			return NULL;

		if (isdn_net_device_started(n))
			return NULL;
		return (isdn_net_new(newname, n->dev));
	}
	return NULL;
}
