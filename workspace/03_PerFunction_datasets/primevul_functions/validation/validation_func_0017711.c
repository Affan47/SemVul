UnicodeString UnicodeString::unescape() const {
    UnicodeString result(length(), (UChar32)0, (int32_t)0);
    if (result.isBogus()) {
        return result;
    }
    const UChar *array = getBuffer();
    int32_t len = length();
    int32_t prev = 0;
    for (int32_t i=0;;) {
        if (i == len) {
            result.append(array, prev, len - prev);
            break;
        }
        if (array[i++] == 0x5C ) {
            result.append(array, prev, (i - 1) - prev);
            UChar32 c = unescapeAt(i);
            if (c < 0) {
                result.remove();
                break;
            }
            result.append(c);
            prev = i;
        }
    }
    return result;
}
