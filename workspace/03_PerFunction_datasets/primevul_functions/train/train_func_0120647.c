char *fzofft(__G__ val, pre, post)
    __GDEF
    zoff_t val;
    ZCONST char *pre;
    ZCONST char *post;
{


    char fmt[16];


    fmt[0] = '%';
    fmt[1] = '\0';
    if (pre == FZOFFT_HEX_WID)
    {
        strcat(fmt, FZOFFT_HEX_WID_VALUE);
    }
    else if (pre == FZOFFT_HEX_DOT_WID)
    {
        strcat(fmt, ".");
        strcat(fmt, FZOFFT_HEX_WID_VALUE);
    }
    else if (pre != NULL)
    {
        strcat(fmt, pre);
    }

    strcat(fmt, FZOFFT_FMT);

    if (post == NULL)
        strcat(fmt, "d");
    else
        strcat(fmt, post);


    G.fzofft_index = (G.fzofft_index + 1) % FZOFFT_NUM;


    sprintf(G.fzofft_buf[G.fzofft_index], fmt, val);


    return G.fzofft_buf[G.fzofft_index];
}
