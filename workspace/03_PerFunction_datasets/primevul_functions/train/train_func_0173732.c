Jsi_OptionSpecsCached(Jsi_Interp *interp, const Jsi_OptionSpec *staticSpecs)
{
#ifdef NO_CACHED_SPECS
    return (Jsi_OptionSpec*)staticSpecs;
#else

    if (interp->mainInterp == NULL) {
        interp->mainInterp = interp;
    }
    if (interp == interp->mainInterp) {
        return staticSpecs;
    }
    return jsi_GetCachedOptionSpecs(interp, staticSpecs);
#endif
}
