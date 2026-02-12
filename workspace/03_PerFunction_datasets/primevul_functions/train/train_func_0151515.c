normalize_cookie_domain (const char *domain)
{


	if (domain != NULL && domain[0] == '.')
		return domain + 1;
	return domain;
}
