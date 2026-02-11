copyfile(char *oldpath, char *newpath)
{
	int	fi,fo,x;
	char	buf[512];
	struct	stat st;

	fi = open(oldpath,O_RDONLY,0);
	if(fi < 0)
		return 1;

	fstat(fi,&st);
	if(!(st.st_mode & S_IFREG))
		return 3;

	fo = creat(newpath,(int)(st.st_mode & 0777));
	if(fo < 0)
	{
		close(fi);
		return 2;
	}
	for(x=1; x>0; )
	{
		x = read(fi,buf,512);
		if(x > 0)
		{
			if(write(fo,buf,x) < x)
			{
				close(fo);
				close(fi);
				unlink(newpath);
				return 4;
			}
		}
	}
	close(fo);
	close(fi);

	return 0;
}
