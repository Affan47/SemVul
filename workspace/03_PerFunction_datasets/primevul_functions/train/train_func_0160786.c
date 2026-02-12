static inline UObject* objectClone(const UObject* a) {

    return ((const Measure*) a)->clone();
}
