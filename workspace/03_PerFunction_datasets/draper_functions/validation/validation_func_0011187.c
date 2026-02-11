to_side(const char *str) {
    int i = NUM_SIDES;
    for (; i > 0; ) {
        i -= 2;
        if (strcasecmp(str, sides[i]) == 0) return i >> 1;
    }
    return -1;
}
