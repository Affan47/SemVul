b_resize()
{
    char **src;
    int src_lines,i;
    char line[BUFFER_SIZE],*lp;
    int cont;
    int color;

    src_lines=b_bottom-b_first;
    if (term_width==COLS)
        return;
    term_width=COLS;


    if (!(src=CALLOC(src_lines,char*)))
        syserr("Out of memory");
    if (b_bottom>b_first)
        memcpy(src,b_output+(b_first%B_LENGTH),src_lines*sizeof(char*));
    else
    {
        memcpy(src,b_output+(b_first%B_LENGTH),(B_LENGTH-b_first%B_LENGTH)*sizeof(char*));
        memcpy(src+B_LENGTH-b_first%B_LENGTH,b_output,(b_bottom%B_LENGTH)*sizeof(char*));
    }
    o_len=o_pos=0;
    o_oldcolor=o_prevcolor=o_lastprevcolor=7;
    if (b_greeting>=b_first)
        b_greeting-=b_first;
    b_bottom=b_current=b_last=b_first=0;
    lp=line;
    cont=0;
    color=-1;
    for(i=0;i<src_lines;i++)
    {
        int ncolor=color;
        char *sp=src[i];
        if (cont && *sp=='~' && getcolor(&sp,&ncolor,0))
        {

            if (color!=ncolor)
                sp=src[i];
        }
        while (*sp && lp-line<BUFFER_SIZE-2)
            *lp++=*sp++;
        SFREE(src[i]);
        if ((cont=(lp>line && lp[-1]=='\r')))
            lp--;
        else
        {
            *lp++='\n';
            *lp=0;
            b_textout(line);
            lp=line;
        }
    }
    assert(!cont);
    CFREE(src,src_lines,char*);
    if (o_draftlen)
        b_textout(b_draft);
}
