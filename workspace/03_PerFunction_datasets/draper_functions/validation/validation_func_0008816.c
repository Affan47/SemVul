delChar(cldata)
caddr_t cldata;
{
    CcWnnObject obj = (CcWnnObject)cldata;

    if (obj->ccWnn.state != normal_state) {
	beep(obj);
	return;
    }
    ccContextDelete(obj->ccWnn.ccbuf);
    jcDeleteChar(obj->ccWnn.jcbuf, 1);
    obj->ccWnn.textchanged = True;
}
