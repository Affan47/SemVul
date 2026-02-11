readcmd(String *s)
{
	int retcode;

	if(flist != 0)
		fileclose(flist);
	flist = fileopen();

	addr.r.p1 = 0, addr.r.p2 = flist->b.nc;
	retcode = plan9(flist, '<', s, FALSE);
	fileupdate(flist, FALSE, FALSE);
	flist->seq = 0;
	if (flist->b.nc > BLOCKSIZE)
		error(Etoolong);
	Strzero(&genstr);
	Strinsure(&genstr, flist->b.nc);
	bufread(&flist->b, (Posn)0, genbuf, flist->b.nc);
	memmove(genstr.s, genbuf, flist->b.nc*RUNESIZE);
	genstr.n = flist->b.nc;
	Straddc(&genstr, '\0');
	return retcode;
}
