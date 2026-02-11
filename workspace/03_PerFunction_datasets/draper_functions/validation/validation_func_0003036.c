clone_hv_to(pTHX_ pMY_CXT_ HV* const cloning, HV* const cloned) {
    HE* iter;

    assert(cloning);
    assert(cloned);

    hv_iterinit(cloning);
    while((iter = hv_iternext(cloning))){
        SV* const key = hv_iterkeysv(iter);
        SV* const val = clone_sv(aTHX_ aMY_CXT_ hv_iterval(cloning, iter));
        (void)hv_store_ent(cloned, key, val, 0U);
    }
}
