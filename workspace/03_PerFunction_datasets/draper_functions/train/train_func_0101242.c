TooBig(F, maxsize)
    FILE	*F;
    OFFSET_T	maxsize;
{
    struct stat	Sb;


    if (fstat((int)fileno(F), &Sb) < 0) {
	(void)fprintf(stderr,
	  "%s: Can't fstat, %s\n", program, strerror(errno));
	return FALSE;
    }


    return (maxsize > Sb.st_size ? FALSE : TRUE);
}
