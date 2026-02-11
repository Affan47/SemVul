readps2(int fd)
{
	char ch;

	while(read(fd,&ch,1) && (ch==(char)0xfa || ch==(char)0xaa))
	{
		fprintf(stderr,"<%02X>",ch&0xff);
		fflush(stdout);
	}
	return(ch);
}
