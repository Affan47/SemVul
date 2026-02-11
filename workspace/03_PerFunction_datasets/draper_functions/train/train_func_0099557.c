kindConstr(line,alpha,m,c)
Int  line;
Int  alpha;
Int  m;
Cell c; {
    Cell h = getHead(c);
    Int  n = argCount;

#if DEBUG_KINDS
    Printf("kindConstr: alpha=%d, m=%d, c=",alpha,m);
    printType(stdout,c);
    Printf("\n");
#endif

    switch (whatIs(h)) {
	case POLYTYPE : if (n!=0) {
			    internal("kindConstr1");
			} else {
			    static String pt = "polymorphic type";
			    Type  t  = dropRank1(c,alpha,m);
			    Kinds ks = polySigOf(t);
			    Int   m1 = 0;
			    Int   beta;
			    for (; isAp(ks); ks=tl(ks)) {
				m1++;
			    }
			    beta	= newKindvars(m1);
			    unkindTypes = cons(pair(mkInt(beta),t),unkindTypes);
			    checkKind(line,beta,m1,monotypeOf(t),NIL,pt,STAR,0);
			}
			return;

	case CDICTS   :
	case QUAL     : if (n!=0) {
			    internal("kindConstr2");
			}
			map3Proc(kindPred,line,alpha,m,fst(snd(c)));
			kindConstr(line,alpha,m,snd(snd(c)));
			return;

	case EXIST    :
	case RANK2    : kindConstr(line,alpha,m,snd(snd(c)));
			return;

#if TREX
	case EXT      : if (n!=2) {
			    ERRMSG(line)
				"Illegal use of row in " ETHEN ERRTYPE(c);
			    ERRTEXT "\n"
			    EEND;
			}
			break;
#endif

	case TYCON    : if (isSynonym(h) && n<tycon(h).arity) {
			    ERRMSG(line)
			      "Not enough arguments for type synonym \"%s\"",
			      textToStr(tycon(h).text)
			    EEND;
			}
			break;
    }

    if (n==0) {
	typeIs = kindAtom(alpha,c);
    } else {
	static String app = "constructor application";
	Cell   a = c;
	Int    i;
	Kind   k;
	Int    beta;

	varKind(n);
	beta   = typeOff;
	k      = typeIs;

	typeIs = kindAtom(alpha,h);
	shouldKind(line,h,c,app,k,beta);

	for (i=n; i>0; --i) {
	    checkKind(line,alpha,m,arg(a),c,app,aVar,beta+i-1);
	    a = fun(a);
	}
	tyvarType(beta+n);
    }
}
