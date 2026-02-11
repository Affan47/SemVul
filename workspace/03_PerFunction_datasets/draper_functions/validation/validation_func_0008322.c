_set_attr_substrlen(int index, char *str, int **substrlens)
{
	char *p = NULL;


	p = strchr(str, '=');
	if (NULL != p) {
		long sublen = strtol(++p, (char **)NULL, 10);
		if (sublen > 0) {
			if (NULL == *substrlens) {
				*substrlens = (int *)slapi_ch_calloc(1,
												sizeof(int) * INDEX_SUBSTRLEN);
			}
			(*substrlens)[index] = sublen;
		}
	}
}
