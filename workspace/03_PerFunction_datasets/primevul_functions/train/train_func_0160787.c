static inline UBool objectEquals(const UObject* a, const UObject* b) {

    return *((const Measure*) a) == *((const Measure*) b);
}
