mark_file(arg)
CONST char *arg;
{
	if (isdir(&(filelist[filepos]))) return(FNC_NONE);
	filelist[filepos].tmpflags ^= F_ISMRK;
	if (ismark(&(filelist[filepos]))) {
		mark++;
		if (isfile(&(filelist[filepos])))
			marksize += getblock(filelist[filepos].st_size);
	}
	else {
		mark--;
		if (isfile(&(filelist[filepos])))
			marksize -= getblock(filelist[filepos].st_size);
	}
	markcount();

	return(FNC_UPDATE);
}
