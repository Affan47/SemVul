pathcat(char *buf, char **path, char *file)
{
    register int n = 0;

    while(**path && **path != ':'){
	if(n++ > MAXPATH)
	  return(FALSE);

	*buf++ = *(*path)++;
    }

    if(n){
	if(n++ > MAXPATH)
	  return(FALSE);

	*buf++ = '/';
    }

    while((*buf = *file++) != '\0'){
	if(n++ > MAXPATH)
	  return(FALSE);

	buf++;
    }

    if(**path == ':')
      (*path)++;

    return(TRUE);
}
