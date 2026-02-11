runIO(n)
int n; {

    StackPtr old_sp   = sp - n - 1;
    Cell     temp     = NIL;
    Int i;

    for(i=n-1; i >= 0; --i) {
	pushed(n) = ap(pushed(n), pushed(i));
    }
    sp -= n;


    temp = evalWithNoError(ap(nameIORun,pop()));
    if (nonNull(temp)) {
	ERRMSG(0) "runIO: uncaught error"
	EEND;
    }
    if (sp != old_sp+1) {
	ERRMSG(0) "runIO: unbalanced stack (%d)", sp-old_sp
	EEND;
    }
    if (whnfHead == nameRight) {
	return 0;
    } else if (whnfHead != nameLeft) {
	ERRMSG(0) "runIO: bad return value"
	EEND;
    }
    return 1;
}
