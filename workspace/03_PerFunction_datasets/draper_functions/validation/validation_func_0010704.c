handleGetTrailSurrogate() {
    if(state != IN_NORMALIZED) { return 0; }
    U_ASSERT(pos < normalized.length());
    UChar trail;
    if(U16_IS_TRAIL(trail = normalized[pos])) { ++pos; }
    return trail;
}
