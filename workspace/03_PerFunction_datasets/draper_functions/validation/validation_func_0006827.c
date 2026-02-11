mkfunode(fun,n)
truc fun;
int n;
{
    struct funode *node;
    truc obj;
    truc *ptr;
    int flg, sflg;

    sflg = Symflag(fun);
    if(sflg == sFBINARY) {
        flg = fBUILTINn;
    }
    else if(sflg == sSBINARY) {
        flg = fSPECIALn;
    }
    else
        flg = fFUNCALL;

    obj = newobj(flg,SIZEOFFUNODE(n),(trucptr *)&node);
    node->op = fun;
    node->argno = mkfixnum(n);
    ptr = (truc *)&(node->arg1);
    while(--n >= 0) {
        *ptr++ = argStkPtr[-n];
    }
    return(obj);
}
