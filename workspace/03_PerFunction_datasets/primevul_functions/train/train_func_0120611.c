int do_string(__G__ length, option)
    __GDEF
    unsigned int length;
    int option;
{
    unsigned comment_bytes_left;
    unsigned int block_len;
    int error=PK_OK;
#ifdef AMIGA
    char tmp_fnote[2 * AMIGA_FILENOTELEN];
#endif


    if (!length)
        return PK_COOL;

    switch (option) {

#if (defined(SFX) && defined(CHEAP_SFX_AUTORUN))


    case CHECK_AUTORUN:
    case CHECK_AUTORUN_Q:
        comment_bytes_left = length;
        if (length >= 10)
        {
            block_len = readbuf(__G__ (char *)G.outbuf, 10);
            if (block_len == 0)
                return PK_EOF;
            comment_bytes_left -= block_len;
            G.outbuf[block_len] = '\0';
            if (!strcmp((char *)G.outbuf, "$AUTORUN$>")) {
                char *eol;
                length -= 10;
                block_len = readbuf(__G__ G.autorun_command,
                                    MIN(length, sizeof(G.autorun_command)-1));
                if (block_len == 0)
                    return PK_EOF;
                comment_bytes_left -= block_len;
                G.autorun_command[block_len] = '\0';
                A_TO_N(G.autorun_command);
                eol = strchr(G.autorun_command, '\n');
                if (!eol)
                    eol = G.autorun_command + strlen(G.autorun_command) - 1;
                length -= eol + 1 - G.autorun_command;
                while (eol >= G.autorun_command && isspace(*eol))
                    *eol-- = '\0';
#if (defined(WIN32) && !defined(_WIN32_WCE))


                INTERN_TO_OEM(G.autorun_command, G.autorun_command);
#endif
            }
        }
        if (option == CHECK_AUTORUN_Q)
            length = 0;


        seek_zipf(__G__ G.cur_zipfile_bufstart - G.extra_bytes +
                  (G.inptr - G.inbuf) + comment_bytes_left - length);
        if (!length)
            break;

#endif


    case DISPLAY:
    case DISPL_8:
        comment_bytes_left = length;
        block_len = OUTBUFSIZ;
        while (comment_bytes_left > 0 && block_len > 0) {
            register uch *p = G.outbuf;
            register uch *q = G.outbuf;

            if ((block_len = readbuf(__G__ (char *)G.outbuf,
                   MIN((unsigned)OUTBUFSIZ, comment_bytes_left))) == 0)
                return PK_EOF;
            comment_bytes_left -= block_len;


            G.outbuf[block_len] = '\0';


            while (*p) {
                while (*p == CR)
                    ++p;
                *q++ = *p++;
            }

            *q = '\0';

            if (option == DISPL_8) {


                Ext_ASCII_TO_Native((char *)G.outbuf, G.pInfo->hostnum,
                                    G.pInfo->hostver, G.pInfo->HasUxAtt,
                                    FALSE);
#ifdef WINDLL

                INTERN_TO_ISO((char *)G.outbuf, (char *)G.outbuf);
#else
#if (defined(WIN32) && !defined(_WIN32_WCE))


                INTERN_TO_OEM((char *)G.outbuf, (char *)G.outbuf);
#endif
#endif
            } else {
                A_TO_N(G.outbuf);
            }

#ifdef WINDLL

            win_fprintf((zvoid *)&G, stdout, (extent)(q-G.outbuf),
                        (char *)G.outbuf);
            win_fprintf((zvoid *)&G, stdout, 2, (char *)"\n\n");
#else
#ifdef NOANSIFILT
            (*G.message)((zvoid *)&G, G.outbuf, (ulg)(q-G.outbuf), 0);
#else
            p = G.outbuf - 1;
            q = slide;
            while (*++p) {
                int pause = FALSE;

                if (*p == 0x1B) {
                    *q++ = '^';
                    *q++ = '[';
                } else if (*p == 0x13) {
                    pause = TRUE;
                    if (p[1] == LF)
                        *q++ = *++p;
                    else if (p[1] == CR && p[2] == LF) {
                        *q++ = *++p;
                        *q++ = *++p;
                    }
                } else
                    *q++ = *p;
                if ((unsigned)(q-slide) > WSIZE-3 || pause) {
                    (*G.message)((zvoid *)&G, slide, (ulg)(q-slide), 0);
                    q = slide;
                    if (pause && G.extract_flag)
                        (*G.mpause)((zvoid *)&G, LoadFarString(QuitPrompt), 0);
                }
            }
            (*G.message)((zvoid *)&G, slide, (ulg)(q-slide), 0);
#endif
#endif
        }

        (*G.message)((zvoid *)&G, slide, 0L, 0x40);
        break;


    case DS_FN:
    case DS_FN_L:
#ifdef UNICODE_SUPPORT

        if (G.fnfull_bufsize <= length) {
            extent fnbufsiz = FILNAMSIZ;

            if (fnbufsiz <= length)
                fnbufsiz = length + 1;
            if (G.filename_full)
                free(G.filename_full);
            G.filename_full = malloc(fnbufsiz);
            if (G.filename_full == NULL)
                return PK_MEM;
            G.fnfull_bufsize = fnbufsiz;
        }
        if (readbuf(__G__ G.filename_full, length) == 0)
            return PK_EOF;
        G.filename_full[length] = '\0';


        if (length >= FILNAMSIZ) {
            Info(slide, 0x401, ((char *)slide,
              LoadFarString(FilenameTooLongTrunc)));
            error = PK_WARN;
            length = FILNAMSIZ - 1;
        }

        block_len = 0;
        strncpy(G.filename, G.filename_full, length);
        G.filename[length] = '\0';
#else
        if (length >= FILNAMSIZ) {
            Info(slide, 0x401, ((char *)slide,
              LoadFarString(FilenameTooLongTrunc)));
            error = PK_WARN;

            block_len = length - (FILNAMSIZ - 1);
            length = FILNAMSIZ - 1;
        } else

            block_len = 0;
        if (readbuf(__G__ G.filename, length) == 0)
            return PK_EOF;
        G.filename[length] = '\0';
#endif


        Ext_ASCII_TO_Native(G.filename, G.pInfo->hostnum, G.pInfo->hostver,
                            G.pInfo->HasUxAtt, (option == DS_FN_L));

        if (G.pInfo->lcflag)
            STRLOWER(G.filename, G.filename);

        if (G.pInfo->vollabel && length > 8 && G.filename[8] == '.') {
            char *p = G.filename+8;
            while (*p++)
                p[-1] = *p;
        }

        if (!block_len)
            break;


        Info(slide, 0x401, ((char *)slide, "[ %s ]\n", FnFilter1(G.filename)));
        length = block_len;


    case SKIP:


        seek_zipf(__G__ G.cur_zipfile_bufstart - G.extra_bytes +
                  (G.inptr-G.inbuf) + length);
        break;


    case EXTRA_FIELD:
        if (G.extra_field != (uch *)NULL)
            free(G.extra_field);
        if ((G.extra_field = (uch *)malloc(length)) == (uch *)NULL) {
            Info(slide, 0x401, ((char *)slide, LoadFarString(ExtraFieldTooLong),
              length));


            seek_zipf(__G__ G.cur_zipfile_bufstart - G.extra_bytes +
                      (G.inptr-G.inbuf) + length);
        } else {
            if (readbuf(__G__ (char *)G.extra_field, length) == 0)
                return PK_EOF;

            getZip64Data(__G__ G.extra_field, length);
#ifdef UNICODE_SUPPORT
            G.unipath_filename = NULL;
            if (G.UzO.U_flag < 2) {


              if (G.pInfo->GPFIsUTF8) {

                G.unipath_filename = G.filename_full;
              } else {

                getUnicodeData(__G__ G.extra_field, length);
                if (G.unipath_filename && strlen(G.unipath_filename) == 0) {

                  free(G.unipath_filename);
                  G.unipath_filename = G.filename_full;
                }
              }
              if (G.unipath_filename) {
# ifdef UTF8_MAYBE_NATIVE
                if (G.native_is_utf8
#  ifdef UNICODE_WCHAR
                    && (!G.unicode_escape_all)
#  endif
                   ) {
                  strncpy(G.filename, G.unipath_filename, FILNAMSIZ - 1);

                  if (strlen(G.unipath_filename) >= FILNAMSIZ) {
                    G.filename[FILNAMSIZ - 1] = '\0';
                    Info(slide, 0x401, ((char *)slide,
                      LoadFarString(UFilenameTooLongTrunc)));
                    error = PK_WARN;
                  }
                }
#  ifdef UNICODE_WCHAR
                else
#  endif
# endif
# ifdef UNICODE_WCHAR
                {
                  char *fn;


                  fn = utf8_to_local_string(G.unipath_filename,
                                            G.unicode_escape_all);

                  if (strlen(fn) >= FILNAMSIZ) {
                    fn[FILNAMSIZ - 1] = '\0';
                    Info(slide, 0x401, ((char *)slide,
                      LoadFarString(UFilenameTooLongTrunc)));
                    error = PK_WARN;
                  }

                  strcpy(G.filename, fn);
                  free(fn);
                }
# endif
                if (G.unipath_filename != G.filename_full)
                  free(G.unipath_filename);
                G.unipath_filename = NULL;
              }
            }
#endif
        }
        break;

#ifdef AMIGA


    case FILENOTE:
        if ((block_len = readbuf(__G__ tmp_fnote, (unsigned)
                                 MIN(length, 2 * AMIGA_FILENOTELEN - 1))) == 0)
            return PK_EOF;
        if ((length -= block_len) > 0)
            seek_zipf(__G__ G.cur_zipfile_bufstart - G.extra_bytes
                      + (G.inptr - G.inbuf) + length);

        tmp_fnote[block_len] = '\0';
        while ((short int) --block_len >= 0)
            if ((unsigned) tmp_fnote[block_len] < ' ')
                if (tmp_fnote[block_len+1] == ' ')
                    strcpy(tmp_fnote+block_len, tmp_fnote+block_len+1);
                else
                    tmp_fnote[block_len] = ' ';
        tmp_fnote[AMIGA_FILENOTELEN - 1] = '\0';
        if (G.filenotes[G.filenote_slot])
            free(G.filenotes[G.filenote_slot]);
        G.filenotes[G.filenote_slot] = NULL;
        if (tmp_fnote[0]) {
            if (!(G.filenotes[G.filenote_slot] = malloc(strlen(tmp_fnote)+1)))
                return PK_MEM;
            strcpy(G.filenotes[G.filenote_slot], tmp_fnote);
        }
        break;
#endif

    }

    return error;

}
