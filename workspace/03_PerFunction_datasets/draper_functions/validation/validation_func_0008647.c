clone_sv(pTHX_ pMY_CXT_ SV* const cloning) {
    assert(cloning);

    SvGETMAGIC(cloning);

    if(SvROK(cloning)){
        return clone_rv(aTHX_ aMY_CXT_ cloning);
    }
    else{
        SV* const cloned = newSV(0);

        sv_setsv_flags(cloned, cloning, SV_NOSTEAL);
        return cloned;
    }
}
