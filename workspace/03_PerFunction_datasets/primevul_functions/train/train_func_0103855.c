crypto_key(
	char	*cp,
	char	*passwd1,
	sockaddr_u *addr
	)
{
	FILE	*str;
	struct pkey_info *pkp;
	EVP_PKEY *pkey = NULL;
	tstamp_t fstamp;
	char	filename[MAXFILENAME];
	char	linkname[MAXFILENAME];
	char	statstr[NTP_MAXSTRLEN];
	char	*ptr;


	for (pkp = pkinfo; pkp != NULL; pkp = pkp->link) {
		if (strcmp(cp, pkp->name) == 0)
			return (pkp);
	}


	if (*cp == '/')
		strlcpy(filename, cp, sizeof(filename));
	else
		snprintf(filename, sizeof(filename), "%s/%s", keysdir,
		    cp);
	str = fopen(filename, "r");
	if (str == NULL)
		return (NULL);


	if ((ptr = fgets(linkname, sizeof(linkname), str)) == NULL) {
		msyslog(LOG_ERR, "crypto_key: empty file %s",
		    filename);
		fclose(str);
		return (NULL);
	}
	if ((ptr = strrchr(ptr, '.')) == NULL) {
		msyslog(LOG_ERR, "crypto_key: no filestamp %s",
		    filename);
		fclose(str);
		return (NULL);
	}
	if (sscanf(++ptr, "%u", &fstamp) != 1) {
		msyslog(LOG_ERR, "crypto_key: invalid filestamp %s",
		    filename);
		fclose(str);
		return (NULL);
	}


	pkey = PEM_read_PrivateKey(str, NULL, NULL, passwd1);
	fclose(str);
	if (pkey == NULL) {
		msyslog(LOG_ERR, "crypto_key: %s",
		    ERR_error_string(ERR_get_error(), NULL));
		exit (-1);
	}


	pkp = emalloc(sizeof(struct pkey_info));
	pkp->link = pkinfo;
	pkinfo = pkp;
	pkp->pkey = pkey;
	pkp->name = estrdup(cp);
	pkp->fstamp = fstamp;


	if ((ptr = strrchr(linkname, '\n')) != NULL)
		*ptr = '\0';
	snprintf(statstr, sizeof(statstr), "%s mod %d", &linkname[2],
	    EVP_PKEY_size(pkey) * 8);
	record_crypto_stats(addr, statstr);

	DPRINTF(1, ("crypto_key: %s\n", statstr));
#ifdef DEBUG
	if (debug > 1) {
		if (pkey->type == EVP_PKEY_DSA)
			DSA_print_fp(stdout, pkey->pkey.dsa, 0);
		else if (pkey->type == EVP_PKEY_RSA)
			RSA_print_fp(stdout, pkey->pkey.rsa, 0);
	}
#endif
	return (pkp);
}
