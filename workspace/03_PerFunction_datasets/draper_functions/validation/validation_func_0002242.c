addElement(int32_t elem, UErrorCode &status) {
    if (ensureCapacity(count + 1, status)) {
        elements[count].pointer = NULL;
        elements[count].integer = elem;
        count++;
    }
}
