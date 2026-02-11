nextWord(int p, bool sep) {
    int textLen = fText.length();

    while (p < textLen &&
           (CHCLASS(fText.charAt(p)) == CHCLASS(fText.charAt(p + 1)) ||
            (!sep && CHCLASS(fText.charAt(p)))))
    {
        p++;
    }
    if (p < textLen)
        p++;
    return p;
}
