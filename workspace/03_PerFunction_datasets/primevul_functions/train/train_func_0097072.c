static bool isControlChar(UChar32 testChar) {
    return (testChar < ' ') ||
        (testChar >= 0x7F && testChar <= 0x9F);
}
