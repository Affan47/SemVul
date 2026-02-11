handleNextCE32(UChar32 &c, UErrorCode & ) {
    if(pos == limit) {
        c = U_SENTINEL;
        return Collation::FALLBACK_CE32;
    }
    c = *pos++;
    return UTRIE2_GET32_FROM_U16_SINGLE_LEAD(trie, c);
}
