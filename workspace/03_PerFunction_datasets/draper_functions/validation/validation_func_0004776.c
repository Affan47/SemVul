print_session(const char *val)
{
	if (strcmp(val, "4294967295") == 0)
		return strdup("unset");
	else
		return strdup(val);
}
