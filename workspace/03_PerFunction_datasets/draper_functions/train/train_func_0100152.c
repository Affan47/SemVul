getMwmHints() {
    if (!prop.mwm_hints)
        return;

    int retFormat;
    Atom retType;
    unsigned long retCount, remain;

    if (fMwmHints) {
        XFree(fMwmHints);
        fMwmHints = 0;
    }
    union {
        MwmHints *ptr;
        unsigned char *xptr;
    } mwmHints = { 0 };

    if (XGetWindowProperty(xapp->display(), handle(),
                           _XATOM_MWM_HINTS, 0L, 20L, False, _XATOM_MWM_HINTS,
                           &retType, &retFormat, &retCount,
                           &remain, &(mwmHints.xptr)) == Success && mwmHints.ptr)
    {
        if (retCount >= PROP_MWM_HINTS_ELEMENTS) {
            fMwmHints = mwmHints.ptr;
            return;
        } else
            XFree(mwmHints.xptr);
    }
    fMwmHints = 0;
}
