crypto_cert(
	char	*cp
	)
{
	struct cert_info *ret;
	FILE	*str;
	char	filename[MAXFILENAME];
	char	linkname[MAXFILENAME];
	char	statstr[NTP_MAXSTRLEN];
	tstamp_t fstamp;
	long	len;
	char	*ptr;
	char	*name, *header;
	u_char	*data;


	if (*cp == '/')
		strlcpy(filename, cp, sizeof(filename));
	else
		snprintf(filename, sizeof(filename), "%s/%s", keysdir,
		    cp);
	str = fopen(filename, "r");
	if (str == NULL)
		return (NULL);


	if ((ptr = fgets(linkname, sizeof(linkname), str)) == NULL) {
		msyslog(LOG_ERR, "crypto_cert: empty file %s",
		    filename);
		fclose(str);
		return (NULL);
	}
	if ((ptr = strrchr(ptr, '.')) == NULL) {
		msyslog(LOG_ERR, "crypto_cert: no filestamp %s",
		    filename);
		fclose(str);
		return (NULL);
	}
	if (sscanf(++ptr, "%u", &fstamp) != 1) {
		msyslog(LOG_ERR, "crypto_cert: invalid filestamp %s",
		    filename);
		fclose(str);
		return (NULL);
	}


	if (!PEM_read(str, &name, &header, &data, &len)) {
		msyslog(LOG_ERR, "crypto_cert: %s",
		    ERR_error_string(ERR_get_error(), NULL));
		fclose(str);
		return (NULL);
	}
	fclose(str);
	free(header);
	if (strcmp(name, "CERTIFICATE") != 0) {
		msyslog(LOG_NOTICE, "crypto_cert: wrong PEM type %s",
		    name);
		free(name);
		free(data);
		return (NULL);
	}
	free(name);


	ret = cert_parse(data, len, fstamp);
	free(data);
	if (ret == NULL)
		return (NULL);

	if ((ptr = strrchr(linkname, '\n')) != NULL)
		*ptr = '\0';
	snprintf(statstr, sizeof(statstr), "%s 0x%x len %lu",
	    &linkname[2], ret->flags, len);
	record_crypto_stats(NULL, statstr);
	DPRINTF(1, ("crypto_cert: %s\n", statstr));
	return (ret);
}
