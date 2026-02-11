sieve_find_script(const char *user, const char *domain,
			     const char *script, char *fname, size_t size)
{
    if (!user && !script) {
	return -1;
    }

    if (user && strlen(user) > 900) {
	return -1;
    }

    if (sieve_usehomedir && user) {
	struct passwd *pent = getpwnam(user);

	if (pent == NULL) {
	    return -1;
	}


	snprintf(fname, size, "%s/%s", pent->pw_dir, script ? script : ".sieve");
    } else {
	size_t len = strlcpy(fname, sieve_dir, size);

	if (domain) {
	    char dhash = (char) dir_hash_c(domain, config_fulldirhash);
	    len += snprintf(fname+len, size-len, "%s%c/%s",
			    FNAME_DOMAINDIR, dhash, domain);
	}

	if (!user) {
	    len = strlcat(fname, "/global/", size);
	}
	else {
	    char hash = (char) dir_hash_c(user, config_fulldirhash);
	    len += snprintf(fname+len, size-len, "/%c/%s/", hash, user);

	    if (!script) {
		strlcat(fname, "defaultbc", size);
		return 0;
	    }
	}

	snprintf(fname+len, size-len, "%s.bc", script);
    }
    return 0;
}
