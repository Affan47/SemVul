typeCompy(l,m,qs)
Int  l;
Type m;
List qs; {
    static String boolQual = "boolean qualifier";
    static String genQual  = "generator";
#if IPARAM
    List svPreds;
#endif

    STACK_CHECK
    if (!isNull(qs)) {
	Cell q   = hd(qs);
	List qs1 = tl(qs);
	switch (whatIs(q)) {
	    case BOOLQUAL : spCheck(l,snd(q),NIL,boolQual,typeBool,0);
			    typeCompy(l,m,qs1);
			    break;

	    case QWHERE   : enterBindings();
			    enterSkolVars();
			    mapProc(typeBindings,snd(q));
			    hd(gatheredAss) = dupOnto(hd(varsBounds),hd(gatheredAss));

			    hd(gatheredDefns) = dupOnto(hd(defnBounds),hd(gatheredDefns));
			    typeCompy(l,m,qs1);
			    leaveBindings();
			    leaveSkolVars(l,typeIs,typeOff,0);
			    break;

	    case FROMQUAL : {   Int beta = newTyvars(1);
				enterPendingBtyvs();
				spCheck(l,snd(snd(q)),NIL,genQual,m,beta);
				enterSkolVars();
				fst(snd(q))
				    = typeFreshPat(l,patBtyvs(fst(snd(q))));
				shouldBe(l,fst(snd(q)),NIL,genQual,aVar,beta);
				hd(gatheredAss) = dupOnto(hd(varsBounds),hd(gatheredAss));
				gatheredTyvars = dupOnto(hd(btyvars),gatheredTyvars);
				gatheredPTyvars = dupOnto(hd(pendingBtyvs),gatheredPTyvars);
				typeCompy(l,m,qs1);
			        leavePendingBtyvsQuietly();
				leaveSkolVars(l,typeIs,typeOff,0);
			    }
			    break;

	    case DOQUAL   : spCheck(l,snd(q),NIL,genQual,m,newTyvars(1));
			    typeCompy(l,m,qs1);
			    break;

	    default:	    internal("typeComp");
	}
    }
}
