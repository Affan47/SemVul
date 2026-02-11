fake_fputs(const char *buf, int fd)
{
    int x;
    x=strlen(buf);
    if(write(fd, buf, x)!=x)
	{
        return(EOF);
    }
    return(x);
}
