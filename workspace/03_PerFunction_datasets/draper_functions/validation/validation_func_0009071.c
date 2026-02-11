compileGlobalFunction(bind)
Pair bind; {
    Name n     = findName(textOf(fst(bind)));
    List defs  = snd(bind);
    Int  arity = length(fst(hd(defs)));

    if (isNull(n))
	internal("compileGlobalFunction");
    compiler(RESET);
    currentName  = n;
    defs = altsMatch(1,arity,NIL,defs);
    newGlobalFunction(n,arity,NIL,arity,lift(arity,NIL,match(arity,defs)));
    name(n).defn = NIL;
}
