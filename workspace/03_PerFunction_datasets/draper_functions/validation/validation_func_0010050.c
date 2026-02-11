handleLetter(StyleContext& sc, WordList* specialSelectorList)
{
    char ident[256];
    int il;
    int state;
    bool doubleColonPresent;

    sc.SetState(SCE_ST_DEFAULT);

    ident[0] = static_cast<char>(sc.ch);
    il = 1;
    while (isAlphaNumeric(sc.chNext)) {
        ident[il++] = static_cast<char>(sc.chNext);
        sc.Forward();
        if (il+2 == sizeof(ident)/sizeof(ident[0]))
            break;
    }

    if (sc.chNext == ':') {
        doubleColonPresent = true;
        ident[il++] = ':';
        sc.Forward();
    }
    else
        doubleColonPresent = false;
    ident[il] = 0;

    if (specialSelectorList->InList(ident))
            state = SCE_ST_SPEC_SEL;
    else if (doubleColonPresent)
            state = SCE_ST_KWSEND;
    else if (isUpper(ident[0]))
        state = SCE_ST_GLOBAL;
    else {
        if (!strcmp(ident, "self"))
            state = SCE_ST_SELF;
        else if (!strcmp(ident, "super"))
            state = SCE_ST_SUPER;
        else if (!strcmp(ident, "nil"))
            state = SCE_ST_NIL;
        else if (!strcmp(ident, "true") || !strcmp(ident, "false"))
            state = SCE_ST_BOOL;
        else
            state = SCE_ST_DEFAULT;
    }

    sc.ChangeState(state);
}
