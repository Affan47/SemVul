pixAddText(PIX         *pix,
           const char  *textstring)
{
char  *newstring;

    PROCNAME("pixAddText");

    if (!pix)
        return ERROR_INT("pix not defined", procName, 1);

    newstring = stringJoin(pixGetText(pix), textstring);
    stringReplace(&pix->text, newstring);
    FREE(newstring);
    return 0;
}
