hashStr(const char *s)
{
    unsigned int h = 0;
    int i;
    for (i=0;s[i];i++) {
	h += s[i]*i;
	}
    return h % STRTBLSIZE;
}
