void UZ_EXP UzpMorePause(pG, prompt, flag)
    zvoid *pG;
    ZCONST char *prompt;
    int flag;
{
    uch c;


    if (!((Uz_Globs *)pG)->sol)
        fprintf(stderr, "\n");

    fprintf(stderr, prompt, ((Uz_Globs *)pG)->numlines);
    fflush(stderr);
    if (flag & 1) {
        do {
            c = (uch)FGETCH(0);
        } while (
#ifdef THEOS
                 c != 17 &&
#endif
                 c != '\r' && c != '\n' && c != ' ' && c != 'q' && c != 'Q');
    } else
        c = (uch)FGETCH(0);


    fprintf(stderr, LoadFarString(HidePrompt));
    fflush(stderr);

    if (
#ifdef THEOS
        (c == 17) ||
#endif
        (ToLower(c) == 'q')) {
        DESTROYGLOBALS();
        EXIT(PK_COOL);
    }

    ((Uz_Globs *)pG)->sol = TRUE;

#ifdef MORE

    if ((flag & 1) && c == ' ')
        ((Uz_Globs *)pG)->lines = 0;
#endif

}
