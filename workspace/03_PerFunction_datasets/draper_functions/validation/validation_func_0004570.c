write(hsStream* S, plResManager* mgr) {
    plAGChannel::write(S, mgr);

    if (!S->getVer().isUruSP())
        fAP.write(S);
}
