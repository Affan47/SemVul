static void jsiPop(Jsi_Interp* interp, int n) {
    int t = n;
    while (t > 0) {
        Assert((interp->framePtr->Sp-t)>=0);


        jsiClearStack(interp,t);
        --t;
    }
    interp->framePtr->Sp -= n;
}
