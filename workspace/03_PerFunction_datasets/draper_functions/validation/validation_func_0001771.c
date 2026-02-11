xlputc(LVAL fptr, int ch)
{
    LVAL lptr;
    FILE *fp;


    ++xlfsize;


    if (fptr == NIL)
        ;


    else if (ustreamp(fptr)) {
        lptr = consa(cvchar(ch));
        if (gettail(fptr))
            rplacd(gettail(fptr),lptr);
        else
            sethead(fptr,lptr);
        settail(fptr,lptr);
    }


    else {
        fp = getfile(fptr);
        if (!fp)
            xlfail("file not open");
        else if (fp == stdout || fp == STDERR)
            ostputc(ch);
        else
            osaputc(ch,fp);
    }
}
