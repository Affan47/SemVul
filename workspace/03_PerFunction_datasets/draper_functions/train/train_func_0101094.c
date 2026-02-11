beep(obj)
CcWnnObject obj;
{
    if (JCBUF(obj)->nClause == 0) return;
    bell(obj);
}
