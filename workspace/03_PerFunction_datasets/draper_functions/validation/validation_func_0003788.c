transConFlds(c,flds)
Name c;
List flds; {
    Cell e = c;
    Int  m = name(c).arity;
    Int  i;
    Text t = name(c).text;
    Cell tStr   = mkStr(t);
    Cell empty  = ap(namePrimThrow, ap(nameRecConError, tStr));

    for (i=m; i>0; i--) {
	e = ap(e,empty);
    }
    for (; nonNull(flds); flds=tl(flds)) {
	Cell a = e;
	for (i=m-sfunPos(fst(hd(flds)),c); i>0; i--)
	    a = fun(a);
	arg(a) = translate(snd(hd(flds)));
    }
    return e;
}
