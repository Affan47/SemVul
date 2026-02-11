printit(int pflag, int tflag)
{
    LVAL fptr,val;


    val = xlgetarg();
    fptr = (moreargs() ? xlgetfile() : getvalue(s_stdout));
    xllastarg();


    xlprint(fptr,val,pflag);


    if (tflag)
        xlterpri(fptr);


    return (val);
}
