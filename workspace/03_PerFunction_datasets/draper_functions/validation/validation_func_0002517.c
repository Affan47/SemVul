xerror(void)
{
    LVAL emsg,arg;


    emsg = xlgastring();
    arg = (moreargs() ? xlgetarg() : s_unbound);
    xllastarg();


    xlerror((char *) getstring(emsg),arg);
    return NIL;
}
