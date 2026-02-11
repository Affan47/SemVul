containsAll(const UVector32& other) const {
    for (int32_t i=0; i<other.size(); ++i) {
        if (indexOf(other.elements[i]) < 0) {
            return FALSE;
        }
    }
    return TRUE;
}
