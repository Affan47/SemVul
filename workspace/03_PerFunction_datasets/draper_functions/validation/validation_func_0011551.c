ftprecvstatus(uh, path, namep, n, ent)
int uh;
CONST char *path;
namelist *namep;
int n, ent;
{
	if (ftpmdtm(uh, path, namep, n, ent) < 0) return(-1);
	if (!(urlhostlist[uh].options & UOP_USENLST)) ;
	else if (ftpsize(uh, path, namep, n, ent) < 0) return(-1);

	return(0);
}
