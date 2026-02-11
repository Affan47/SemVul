user_hash_subs(const char *userid)
{
    char *fname = xmalloc(strlen(config_dir) + sizeof(FNAME_DOMAINDIR) +
			  sizeof(FNAME_USERDIR) + strlen(userid) +
			  sizeof(FNAME_SUBSSUFFIX) + 10);
    char c, *domain;

    if (config_virtdomains && (domain = strchr(userid, '@'))) {
	char d = (char) dir_hash_c(domain+1, config_fulldirhash);
	*domain = '\0';
	c = (char) dir_hash_c(userid, config_fulldirhash);
	sprintf(fname, "%s%s%c/%s%s%c/%s%s", config_dir, FNAME_DOMAINDIR, d,
		domain+1, FNAME_USERDIR, c, userid, FNAME_SUBSSUFFIX);
	*domain = '@';
    }
    else {
	c = (char) dir_hash_c(userid, config_fulldirhash);
	sprintf(fname, "%s%s%c/%s%s", config_dir, FNAME_USERDIR, c, userid,
		FNAME_SUBSSUFFIX);
    }

    return fname;
}
