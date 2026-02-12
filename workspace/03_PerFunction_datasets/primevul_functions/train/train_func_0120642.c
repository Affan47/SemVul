int UZ_EXP UzpMessagePrnt(pG, buf, size, flag)
    zvoid *pG;
    uch *buf;
    ulg size;
    int flag;
{


    int error;
    uch *q=buf, *endbuf=buf+(unsigned)size;
#ifdef MORE
    uch *p=buf;
#if (defined(SCREENWIDTH) && defined(SCREENLWRAP))
    int islinefeed = FALSE;
#endif
#endif
    FILE *outfp;


#if (defined(OS2) && defined(DLL))
    if (MSG_NO_DLL2(flag))
        return 0;
#endif
#ifdef WINDLL
    if (MSG_NO_WDLL(flag))
        return 0;
#endif
#ifdef WINDLL
    if (MSG_NO_WGUI(flag))
        return 0;
#endif


#ifdef DLL
    if (((Uz_Globs *)pG)->redirect_data &&
        !((Uz_Globs *)pG)->redirect_text)
        return 0;
#endif

    if (MSG_STDERR(flag) && !((Uz_Globs *)pG)->UzO.tflag)
        outfp = (FILE *)stderr;
    else
        outfp = (FILE *)stdout;

#ifdef QUERY_TRNEWLN


    if (MSG_MNEWLN(flag)) {
        *endbuf++ = '\n';
        ++size;
    }
#endif

    if (MSG_TNEWLN(flag)) {
        if ((!size && !((Uz_Globs *)pG)->sol) ||
            (size && (endbuf[-1] != '\n')))
        {
            *endbuf++ = '\n';
            ++size;
        }
    }

#ifdef MORE
# ifdef SCREENSIZE

#  if (defined(SCREENWIDTH) && defined(SCREENLWRAP))
    SCREENSIZE(&((Uz_Globs *)pG)->height, &((Uz_Globs *)pG)->width);
#  else
    SCREENSIZE(&((Uz_Globs *)pG)->height, (int *)NULL);
#  endif
    ((Uz_Globs *)pG)->height -= 2;
# else

    ((Uz_Globs *)pG)->height = SCREENLINES - 2;
#  if (defined(SCREENWIDTH) && defined(SCREENLWRAP))
    ((Uz_Globs *)pG)->width = SCREENWIDTH;
#  endif
# endif
#endif

    if (MSG_LNEWLN(flag) && !((Uz_Globs *)pG)->sol) {

#ifdef OS2DLL
        if (!((Uz_Globs *)pG)->redirect_text) {
#endif
            putc('\n', outfp);
            fflush(outfp);
#ifdef MORE
            if (((Uz_Globs *)pG)->M_flag)
            {
#if (defined(SCREENWIDTH) && defined(SCREENLWRAP))
                ((Uz_Globs *)pG)->chars = 0;
#endif
                ++((Uz_Globs *)pG)->numlines;
                ++((Uz_Globs *)pG)->lines;
                if (((Uz_Globs *)pG)->lines >= ((Uz_Globs *)pG)->height)
                    (*((Uz_Globs *)pG)->mpause)((zvoid *)pG,
                      LoadFarString(MorePrompt), 1);
            }
#endif
            if (MSG_STDERR(flag) && ((Uz_Globs *)pG)->UzO.tflag &&
                !isatty(1) && isatty(2))
            {

                putc('\n', stderr);
                fflush(stderr);
            }
#ifdef OS2DLL
        } else
           REDIRECTC('\n');
#endif
        ((Uz_Globs *)pG)->sol = TRUE;
    }


#ifdef MORE
    if (((Uz_Globs *)pG)->M_flag
#ifdef OS2DLL
         && !((Uz_Globs *)pG)->redirect_text
#endif
                                                 )
    {
        while (p < endbuf) {
            if (*p == '\n') {
#if (defined(SCREENWIDTH) && defined(SCREENLWRAP))
                islinefeed = TRUE;
            } else if (SCREENLWRAP) {
                if (*p == '\r') {
                    ((Uz_Globs *)pG)->chars = 0;
                } else {
#  ifdef TABSIZE
                    if (*p == '\t')
                        ((Uz_Globs *)pG)->chars +=
                            (TABSIZE - (((Uz_Globs *)pG)->chars % TABSIZE));
                    else
#  endif
                        ++((Uz_Globs *)pG)->chars;

                    if (((Uz_Globs *)pG)->chars >= ((Uz_Globs *)pG)->width)
                        islinefeed = TRUE;
                }
            }
            if (islinefeed) {
                islinefeed = FALSE;
                ((Uz_Globs *)pG)->chars = 0;
#endif
                ++((Uz_Globs *)pG)->numlines;
                ++((Uz_Globs *)pG)->lines;
                if (((Uz_Globs *)pG)->lines >= ((Uz_Globs *)pG)->height)
                {
                    if ((error = WriteTxtErr(q, p-q+1, outfp)) != 0)
                        return error;
                    fflush(outfp);
                    ((Uz_Globs *)pG)->sol = TRUE;
                    q = p + 1;
                    (*((Uz_Globs *)pG)->mpause)((zvoid *)pG,
                      LoadFarString(MorePrompt), 1);
                }
            }
            INCSTR(p);
        }
        size = (ulg)(p - q);
    }
#endif

    if (size) {
#ifdef OS2DLL
        if (!((Uz_Globs *)pG)->redirect_text) {
#endif
            if ((error = WriteTxtErr(q, size, outfp)) != 0)
                return error;
#ifndef VMS
            fflush(outfp);
#endif
            if (MSG_STDERR(flag) && ((Uz_Globs *)pG)->UzO.tflag &&
                !isatty(1) && isatty(2))
            {

                if ((error = WriteTxtErr(q, size, stderr)) != 0)
                    return error;
                fflush(stderr);
            }
#ifdef OS2DLL
        } else {
            if ((error = REDIRECTPRINT(q, size)) != 0)
                return error;
        }
#endif
        ((Uz_Globs *)pG)->sol = (endbuf[-1] == '\n');
    }
    return 0;

}
