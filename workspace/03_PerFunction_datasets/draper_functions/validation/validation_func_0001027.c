prodRange(line,pats,ls,us,is)
Int  line;
List pats;
Cell ls, us, is; {


    Cell is1 = is;
    List e   = NIL;
    for (; isAp(ls); ls=fun(ls), us=fun(us), is=fun(is)) {
	e = cons(ap(FROMQUAL,pair(arg(is),
				  ap(nameRange,ap2(mkTuple(2),
						   arg(ls),
						   arg(us))))),e);
    }
    e = ap(COMP,pair(is1,e));
    e = singleton(pair(pats,pair(mkInt(line),e)));
    return mkBind("range",e);
}
