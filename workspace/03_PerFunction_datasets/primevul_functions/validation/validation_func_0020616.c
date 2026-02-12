vim_fgets(char_u *buf, int size, FILE *fp)
{
    char	*eof;
#define FGETS_SIZE 200
    char	tbuf[FGETS_SIZE];

    buf[size - 2] = NUL;
#ifdef USE_CR
    eof = fgets_cr((char *)buf, size, fp);
#else
    eof = fgets((char *)buf, size, fp);
#endif
    if (buf[size - 2] != NUL && buf[size - 2] != '\n')
    {
	buf[size - 1] = NUL;


	do
	{
	    tbuf[FGETS_SIZE - 2] = NUL;
#ifdef USE_CR
	    ignoredp = fgets_cr((char *)tbuf, FGETS_SIZE, fp);
#else
	    ignoredp = fgets((char *)tbuf, FGETS_SIZE, fp);
#endif
	} while (tbuf[FGETS_SIZE - 2] != NUL && tbuf[FGETS_SIZE - 2] != '\n');
    }
    return (eof == NULL);
}
