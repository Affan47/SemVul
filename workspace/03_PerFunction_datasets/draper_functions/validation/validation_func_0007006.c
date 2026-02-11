MakeDir(Name)
    char		*Name;
{
    struct stat		Sb;

    if (mkdir(Name, GROUPDIR_MODE) >= 0) {
	if (AmRoot)
	    xchown(Name);
	return TRUE;
    }


    return stat(Name, &Sb) >= 0 && S_ISDIR(Sb.st_mode);
}
