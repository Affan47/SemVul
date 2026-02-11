authdaemon_build_query(const char *service,
				    const char *authtype,
				    const char *user,
				    const char *passwd)
{
    int sz;
    int l = strlen(service)
            + 1
            + strlen(authtype)
            + 1
            + strlen(user)
            + 1
            + strlen(passwd)
            + 1;
    char *buf, n[5];
    if (snprintf(n, sizeof(n), "%d", l) >= (int)sizeof(n))
	return NULL;
    sz = strlen(n) + l + 20;
    if (!(buf = sasl_ALLOC(sz)))
	return NULL;
    snprintf(buf,
             sz,
             "AUTH %s\n%s\n%s\n%s\n%s\n\n",
             n,
             service,
             authtype,
             user,
             passwd);
    return buf;
}
