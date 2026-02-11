skipEndOfLine(FontFilePtr f, int c)
{
    if(c == 0)
        c = FontFileGetc(f);

    for(;;)
        if(c <= 0 || c == '\n')
            return;
        else
            c = FontFileGetc(f);
}
