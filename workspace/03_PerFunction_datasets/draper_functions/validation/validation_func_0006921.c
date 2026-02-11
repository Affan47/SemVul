dumpmergedfile(char *outputname)
{
    MERGE           *mp;
    LINE            **lp;
    FILE            *fp;
    long            count;
    int             conflict;
    int             newconflict;

#if 0
    if ((fc.verbosity > VERBOSE_DEFAULT) && outputname)
        error_raw("[Writing merged lines to \"%s\"]", outputname);
#endif
    if (outputname)
    {
        fp = fopen_and_check(outputname, "w");
    }
    else
    {
        fp = stdout;
        outputname = gettext("standard output");
    }
    conflict = 0;
    for (mp = begmergelist; mp; mp = mp->m_next)
    {
        newconflict = ((mp->m_flags & F_CONFLICT) && !ignoreflag);
        if (newconflict != conflict)
        {
            conflict = newconflict;
            fprintf
            (
                fp,
                conflict ? CONFLICT_BEGIN : CONFLICT_END,
                mp->m_baseline + 1,
                mp->m_fileAline + 1,
                mp->m_fileBline + 1
            );
        }
        if (mp->m_flags == F_OLDDATA)
        {
            lp = &baselines[mp->m_baseline];
            for (count = mp->m_basecount; count > 0; count--)
                fputs((*lp++)->l_data, fp);
            continue;
        }
        if (mp->m_flags & F_INSERTA)
        {
            lp = &fileAlines[mp->m_fileAline];
            for (count = mp->m_fileAcount; count > 0; count--)
                fputs((*lp++)->l_data, fp);
        }
        if (conflict && (mp->m_flags & F_INSERTA) && (mp->m_flags & F_INSERTB))
            fputs(CONFLICT_MIDDLE, fp);
        if (mp->m_flags & F_INSERTB)
        {
            lp = &fileBlines[mp->m_fileBline];
            for (count = mp->m_fileBcount; count > 0; count--)
                fputs((*lp++)->l_data, fp);
        }
    }
    if (conflict)
        fputs(CONFLICT_END, fp);
    fflush_and_check(fp, outputname);
    fclose_and_check(fp, outputname);
}
