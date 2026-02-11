make_successor(char *pathbuf)
{
    int len = strlen(pathbuf);
    if (len > 0 && pathbuf[len-1] == pathsep)
	len--;
    pathbuf[len] = '\001';
    pathbuf[len+1] = '\0';
}
