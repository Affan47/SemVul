succCfun(n)
Name n; {
    if (cfunOf(n)==0)
	return NIL;
    else {
	Int  d = cfunOf(n)+1;
	Addr a = name(n).code;
	return (d>intAt(a+1)) ? NIL : cellAt(a+d+1);
    }
}
