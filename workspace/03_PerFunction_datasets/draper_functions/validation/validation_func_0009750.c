rtbl_set_column_affix_by_id(rtbl_t table, unsigned int id,
			    const char *prefix, const char *suffix)
{
    struct column_data *c = rtbl_get_column_by_id (table, id);

    if (c == NULL)
	return -1;
    if (c->prefix)
	free (c->prefix);
    if(prefix == NULL)
	c->prefix = NULL;
    else {
	c->prefix = strdup (prefix);
	if (c->prefix == NULL)
	    return ENOMEM;
    }

    if (c->suffix)
	free (c->suffix);
    if(suffix == NULL)
	c->suffix = NULL;
    else {
	c->suffix = strdup (suffix);
	if (c->suffix == NULL)
	    return ENOMEM;
    }
    return 0;
}
