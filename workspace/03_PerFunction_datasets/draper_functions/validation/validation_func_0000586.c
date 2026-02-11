checkDefaultDefns() {
    List ds = NIL;

    if (defaultLine!=0) {
	map2Over(depTypeExp,defaultLine,NIL,defaultDefns);
	emptySubstitution();
	unkindTypes = NIL;
	map2Proc(kindType,defaultLine,"default type",defaultDefns);
	fixKinds();
	emptySubstitution();
	mapOver(fullExpand,defaultDefns);
    } else {
	defaultDefns = stdDefaults;
    }

    if (isNull(classNum)) {
	classNum = findClass(findText("Num"));
    }

    for (ds=defaultDefns; nonNull(ds); ds=tl(ds)) {
	if (isNull(provePred(NIL,NIL,ap(classNum,hd(ds))))) {
	    ERRMSG(defaultLine)
		"Default types must be instances of the Num class"
	    EEND;
	}
    }
}
