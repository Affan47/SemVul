blkid_parse_tag_string(const char *token, char **ret_type, char **ret_val)
{
	char *name, *value, *cp;

	DBG(DEBUG_TAG, printf("trying to parse '%s' as a tag\n", token));

	if (!token || !(cp = strchr(token, '=')))
		return -1;

	name = blkid_strdup(token);
	if (!name)
		return -1;
	value = name + (cp - token);
	*value++ = '\0';
	if (*value == '"' || *value == '\'') {
		char c = *value++;
		if (!(cp = strrchr(value, c)))
			goto errout;
		*cp = '\0';
	}
	value = blkid_strdup(value);
	if (!value)
		goto errout;

	*ret_type = name;
	*ret_val = value;

	return 0;

errout:
	free(name);
	return -1;
}
