static void list_md_fn(const EVP_MD *m, const char *from, const char *to, void *arg )
{
    size_t len, n;
    const char *name, *cp, **seen;
    struct hstate *hstate = arg;
    EVP_MD_CTX ctx;
    u_int digest_len;
    u_char digest[EVP_MAX_MD_SIZE];

    if (!m)
        return;

    name = EVP_MD_name(m);


    for( cp = name; *cp; cp++ ) {
	if( islower(*cp) )
	    return;
    }
    len = (cp - name) + 1;


    for (seen = hstate->seen; *seen; seen++)
        if (!strcmp(*seen, name))
	    return;
    n = (seen - hstate->seen) + 2;
    hstate->seen = erealloc(hstate->seen, n * sizeof(*seen));
    hstate->seen[n-2] = name;
    hstate->seen[n-1] = NULL;


    EVP_DigestInit(&ctx, EVP_get_digestbyname(name));
    EVP_DigestFinal(&ctx, digest, &digest_len);
    if (digest_len > (MAX_MAC_LEN - sizeof(keyid_t)))
        return;

    if (hstate->list != NULL)
	len += strlen(hstate->list);
    len += (hstate->idx >= K_PER_LINE)? strlen(K_NL_PFX_STR): strlen(K_DELIM_STR);

    if (hstate->list == NULL) {
	hstate->list = (char *)emalloc(len);
	hstate->list[0] = '\0';
    } else
	hstate->list = (char *)erealloc(hstate->list, len);

    sprintf(hstate->list + strlen(hstate->list), "%s%s",
	    ((hstate->idx >= K_PER_LINE)? K_NL_PFX_STR : K_DELIM_STR),
	    name);
    if (hstate->idx >= K_PER_LINE)
	hstate->idx = 1;
    else
	hstate->idx++;
}
