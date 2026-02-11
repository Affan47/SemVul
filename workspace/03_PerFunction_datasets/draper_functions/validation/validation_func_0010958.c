IWrite(hsStream* S, plResManager* mgr) {
    mgr->writeKey(S, fFacer);
    mgr->writeKey(S, fFacee);
    S->writeFloat(fDot);
    S->writeBool(fEnabled);
}
