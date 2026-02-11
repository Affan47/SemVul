typeWith(line,e)
Int  line;
Cell e; {
    List fs    = snd(snd(e));
    Int  n     = length(fs);
    Int  alpha = newTyvars(2+n);
    Int  i;
    List fs1;
    Cell tIs;
    Cell tOff;
    List dpreds = NIL, dp;
    Cell bs = NIL;


    fst(snd(e)) = typeExpr(line,fst(snd(e)));
    bindTv(alpha,typeIs,typeOff);
    tIs = typeIs;
    tOff = typeOff;

    improve(line,NIL,preds);
    preds = scSimplify(preds);

    for (fs1=fs; nonNull(fs1); fs1=tl(fs1)) {
        Text t = textOf(fst(hd(fs1)));
	Cell p = findIPEvid(t);
	dpreds = cons(p, dpreds);
	if (nonNull(p)) {
	    removeIPEvid(t);
	} else {

	}
    }
    dpreds = rev(dpreds);


    for (fs1=fs, dp=dpreds, i=alpha+2; nonNull(fs1); fs1=tl(fs1), dp=tl(dp), i++) {
	static String with = "with";
        Cell ev = hd(dp);
	snd(hd(fs1)) = typeExpr(line,snd(hd(fs1)));
	bindTv(i,typeIs,typeOff);
	if (nonNull(ev)) {
	    shouldBe(line,fst(hd(fs1)),e,with,snd(fst3(ev)),intOf(snd3(ev)));
	    bs = cons(cons(pair(thd3(ev), cons(triple(NIL, mkInt(line), snd(hd(fs1))), NIL)), NIL), bs);
	}
    }
    typeIs = tIs;
    typeOff = tOff;
    return (ap(LETREC,pair(bs,fst(snd(e)))));
}
