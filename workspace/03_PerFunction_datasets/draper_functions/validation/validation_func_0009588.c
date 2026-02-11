LineIndent() {
    int rc = 1;

    if (BFI(this, BFI_AutoIndent)) {
        int L = VToR(CP.Row);

        switch (BFI(this, BFI_IndentMode)) {
#ifdef CONFIG_INDENT_C
        case INDENT_C: rc = Indent_C(this, L, 1); break;
#endif
#ifdef CONFIG_INDENT_REXX
        case INDENT_REXX: rc = Indent_REXX(this, L, 1); break;
#endif
#ifdef CONFIG_INDENT_SIMPLE
        case INDENT_SIMPLE: rc = Indent_SIMPLE(this, L, 1); break;
#endif
        default: rc = Indent_Plain(this, L, 1); break;
        }
    }
    if (rc == 0) return 0;
    if (BFI(this, BFI_Trim))
        if (TrimLine(VToR(CP.Row)) == 0) return 0;
    return 1;
}
