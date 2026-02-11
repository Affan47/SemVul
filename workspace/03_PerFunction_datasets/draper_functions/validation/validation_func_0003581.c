registerInstance(Transliterator* adoptedPrototype) {
    Mutex lock(&registryMutex);
    UErrorCode ec = U_ZERO_ERROR;
    if (HAVE_REGISTRY(ec)) {
        _registerInstance(adoptedPrototype);
    }
}
