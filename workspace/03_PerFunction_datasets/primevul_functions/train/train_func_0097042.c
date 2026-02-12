static UChar32 setMetaRoutine(UChar32 c) {
    thisKeyMetaCtrl = META;
    if (c == 0x1B) {
        c = readUnicodeCharacter();
        if (c == 0)
            return 0;
        return doDispatch(c, escDispatch);
    }
    return doDispatch(c, initialDispatch);
}
