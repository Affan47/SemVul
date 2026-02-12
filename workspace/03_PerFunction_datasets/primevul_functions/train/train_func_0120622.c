int open_outfile(__G)
    __GDEF
{
#ifdef DLL
    if (G.redirect_data)
        return (redirect_outfile(__G) == FALSE);
#endif
#ifdef QDOS
    QFilename(__G__ G.filename);
#endif
#if (defined(DOS_FLX_NLM_OS2_W32) || defined(ATH_BEO_THS_UNX))
#ifdef BORLAND_STAT_BUG


    if (access(G.filename, 0) == -1) {
        FILE *tmp = fopen(G.filename, "wb+");


        fputc('0', tmp);
        fclose(tmp);
    }
#endif
#ifdef SYMLINKS
    if (SSTAT(G.filename, &G.statbuf) == 0 ||
        lstat(G.filename, &G.statbuf) == 0)
#else
    if (SSTAT(G.filename, &G.statbuf) == 0)
#endif
    {
        Trace((stderr, "open_outfile:  stat(%s) returns 0:  file exists\n",
          FnFilter1(G.filename)));
#ifdef UNIXBACKUP
        if (uO.B_flag) {
            char *tname;
            z_stat tmpstat;
            int blen, flen, tlen;

            blen = strlen(BackupSuffix);
            flen = strlen(G.filename);
            tlen = flen + blen + 6;
            if (tlen >= FILNAMSIZ) {
                tname = (char *)malloc(FILNAMSIZ);
                if (tname == NULL)
                    return 1;
                tlen = FILNAMSIZ - 1 - blen;
                strcpy(tname, G.filename);
                tname[tlen] = '\0';
                if (flen > tlen) flen = tlen;
                tlen = FILNAMSIZ;
            } else {
                tname = (char *)malloc(tlen);
                if (tname == NULL)
                    return 1;
                strcpy(tname, G.filename);
            }
            strcpy(tname+flen, BackupSuffix);

            if (IS_OVERWRT_ALL) {


                if (SSTAT(tname, &tmpstat) == 0)
                    unlink(tname);
            } else {


                unsigned maxtail, i;
                char *numtail = tname + flen + blen;


                maxtail = ( ((~0) >= 99999L) ? 99999 : (~0) );
                switch (tlen - flen - blen - 1) {
                    case 4: maxtail = 9999; break;
                    case 3: maxtail = 999; break;
                    case 2: maxtail = 99; break;
                    case 1: maxtail = 9; break;
                    case 0: maxtail = 0; break;
                }

                for (i = 0; (i < maxtail) && (SSTAT(tname, &tmpstat) == 0);)
                    sprintf(numtail,"%u", ++i);
            }

            if (rename(G.filename, tname) != 0) {
                Info(slide, 0x401, ((char *)slide,
                  LoadFarString(CannotRenameOldFile),
                  FnFilter1(G.filename), strerror(errno)));
                free(tname);
                return 1;
            }
            Trace((stderr, "open_outfile:  %s now renamed into %s\n",
              FnFilter1(G.filename), FnFilter2(tname)));
            free(tname);
        } else
#endif
        {
#ifdef DOS_FLX_OS2_W32
            if (!(G.statbuf.st_mode & S_IWRITE)) {
                Trace((stderr,
                  "open_outfile:  existing file %s is read-only\n",
                  FnFilter1(G.filename)));
                chmod(G.filename, S_IREAD | S_IWRITE);
                Trace((stderr, "open_outfile:  %s now writable\n",
                  FnFilter1(G.filename)));
            }
#endif
#ifdef NLM

            chmod(G.filename, 0);
#endif
            if (unlink(G.filename) != 0) {
                Info(slide, 0x401, ((char *)slide,
                  LoadFarString(CannotDeleteOldFile),
                  FnFilter1(G.filename), strerror(errno)));
                return 1;
            }
            Trace((stderr, "open_outfile:  %s now deleted\n",
              FnFilter1(G.filename)));
        }
    }
#endif
#ifdef RISCOS
    if (SWI_OS_File_7(G.filename,0xDEADDEAD,0xDEADDEAD,G.lrec.ucsize)!=NULL) {
        Info(slide, 1, ((char *)slide, LoadFarString(CannotCreateFile),
          FnFilter1(G.filename), strerror(errno)));
        return 1;
    }
#endif
#ifdef TOPS20
    char *tfilnam;

    if ((tfilnam = (char *)malloc(2*strlen(G.filename)+1)) == (char *)NULL)
        return 1;
    strcpy(tfilnam, G.filename);
    upper(tfilnam);
    enquote(tfilnam);
    if ((G.outfile = fopen(tfilnam, FOPW)) == (FILE *)NULL) {
        Info(slide, 1, ((char *)slide, LoadFarString(CannotCreateFile),
          tfilnam, strerror(errno)));
        free(tfilnam);
        return 1;
    }
    free(tfilnam);
#else
#ifdef MTS
    if (uO.aflag)
        G.outfile = zfopen(G.filename, FOPWT);
    else
        G.outfile = zfopen(G.filename, FOPW);
    if (G.outfile == (FILE *)NULL) {
        Info(slide, 1, ((char *)slide, LoadFarString(CannotCreateFile),
          FnFilter1(G.filename), strerror(errno)));
        return 1;
    }
#else
#ifdef DEBUG
    Info(slide, 1, ((char *)slide,
      "open_outfile:  doing fopen(%s) for reading\n", FnFilter1(G.filename)));
    if ((G.outfile = zfopen(G.filename, FOPR)) == (FILE *)NULL)
        Info(slide, 1, ((char *)slide,
          "open_outfile:  fopen(%s) for reading failed:  does not exist\n",
          FnFilter1(G.filename)));
    else {
        Info(slide, 1, ((char *)slide,
          "open_outfile:  fopen(%s) for reading succeeded:  file exists\n",
          FnFilter1(G.filename)));
        fclose(G.outfile);
    }
#endif
#ifdef NOVELL_BUG_FAILSAFE
    if (G.dne && ((G.outfile = zfopen(G.filename, FOPR)) != (FILE *)NULL)) {
        Info(slide, 0x401, ((char *)slide, LoadFarString(NovellBug),
          FnFilter1(G.filename)));
        fclose(G.outfile);
        return 1;
    }
#endif
    Trace((stderr, "open_outfile:  doing fopen(%s) for writing\n",
      FnFilter1(G.filename)));
    {
#if defined(ATH_BE_UNX) || defined(AOS_VS) || defined(QDOS) || defined(TANDEM)
        mode_t umask_sav = umask(0077);
#endif
#if defined(SYMLINKS) || defined(QLZIP)


        G.outfile = zfopen(G.filename, FOPWR);
#else
        G.outfile = zfopen(G.filename, FOPW);
#endif
#if defined(ATH_BE_UNX) || defined(AOS_VS) || defined(QDOS) || defined(TANDEM)
        umask(umask_sav);
#endif
    }
    if (G.outfile == (FILE *)NULL) {
        Info(slide, 0x401, ((char *)slide, LoadFarString(CannotCreateFile),
          FnFilter1(G.filename), strerror(errno)));
        return 1;
    }
    Trace((stderr, "open_outfile:  fopen(%s) for writing succeeded\n",
      FnFilter1(G.filename)));
#endif
#endif

#ifdef USE_FWRITE
#ifdef DOS_NLM_OS2_W32

    setbuf(G.outfile, (char *)NULL);
#else
#ifndef RISCOS
#ifdef _IOFBF
    setvbuf(G.outfile, (char *)slide, _IOFBF, WSIZE);
#else
    setbuf(G.outfile, (char *)slide);
#endif
#endif
#endif
#endif
#ifdef OS2_W32

    SetFileSize(G.outfile, G.lrec.ucsize);
#endif
    return 0;

}
