expand_shrink_general(obj, shrink, small, conv)
CcWnnObject obj;
int shrink;
int small;
int conv;
{
    int status;

    normalState(obj);

    if (shrink) {
	status = jcShrink(JCBUF(obj), small, conv);
    } else {
	status = jcExpand(JCBUF(obj), small, conv);
    }
    if (status < 0) beep(obj);

    ccContextClear(CCBUF(obj));
    HINT(obj) = True;
}
