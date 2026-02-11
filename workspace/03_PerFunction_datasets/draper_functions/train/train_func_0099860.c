printlines(FILE *fp, FILEINFO *fi, long line, long count, const char *tagstr)
{
    LINE            **lines;
    long            *lnum;
    char            *data;
    long            curlnum;

    line = line - fc.context - 1;
    count += (2 * fc.context);
    if (line < 0)
    {
        count += line;
        line = 0;
    }
    if ((line + count) > fi->f_linecount)
        count = fi->f_linecount - line;
    lines = fi->f_lines + line;
    lnum = fi->f_lnums + line;
    curlnum = *lnum;
    while (count-- > 0)
    {
        while (curlnum < *lnum)
        {
            if (fc.whatflag)
                fprintf(fp, "%s\n", tagstr);
            else if (fc.numflag)
                fprintf(fp, "%c%ld\n", fi->f_tag, curlnum);
            else
                putc('\n', fp);
            curlnum++;
        }
        if (fc.whatflag)
            fprintf(fp, "%s  ", tagstr);
        else if (fc.numflag)
            fprintf(fp, "%c%-7ld ", fi->f_tag, curlnum);
        data = (*lines)->l_data;
        if (fc.whatflag)
            data = detab(data);
        fputs(data, fp);
        lines++;
        lnum++;
        curlnum++;
    }
}
