writeauthflush(int fd)
{
	if (writeptr > buf)
	{
		if (writeauth(fd, buf, writeptr - buf))
			return (-1);
	}
	writeptr=buf;
	writeleft=sizeof(buf);
	return (0);
}
