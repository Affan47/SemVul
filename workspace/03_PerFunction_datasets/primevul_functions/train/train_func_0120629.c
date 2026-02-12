static int partflush(__G__ rawbuf, size, unshrink)
    __GDEF
    uch *rawbuf;
    ulg size;
    int unshrink;
#endif
{
    register uch *p;
    register uch *q;
    uch *transbuf;
#if (defined(SMALL_MEM) || defined(MED_MEM) || defined(VMS_TEXT_CONV))
    ulg transbufsiz;
#endif


    G.crc32val = crc32(G.crc32val, rawbuf, (extent)size);

#ifdef DLL
    if ((G.statreportcb != NULL) &&
        (*G.statreportcb)(__G__ UZ_ST_IN_PROGRESS, G.zipfn, G.filename, NULL))
        return IZ_CTRLC;
#endif

    if (uO.tflag || size == 0L)
        return PK_OK;

    if (G.disk_full)
        return PK_DISK;


    if (!G.pInfo->textmode) {


#ifdef DLL
        if (G.redirect_data) {
#ifdef NO_SLIDE_REDIR
            if (writeToMemory(__G__ rawbuf, (extent)size)) return PK_ERR;
#else
            writeToMemory(__G__ rawbuf, (extent)size);
#endif
        } else
#endif
        if (!uO.cflag && WriteError(rawbuf, size, G.outfile))
            return disk_error(__G);
        else if (uO.cflag && (*G.message)((zvoid *)&G, rawbuf, size, 0))
            return PK_OK;
    } else {
        if (unshrink) {

            transbuf = G.outbuf2;
#if (defined(SMALL_MEM) || defined(MED_MEM) || defined(VMS_TEXT_CONV))
            transbufsiz = TRANSBUFSIZ;
#endif
        } else {

            transbuf = G.outbuf;
#if (defined(SMALL_MEM) || defined(MED_MEM) || defined(VMS_TEXT_CONV))
            transbufsiz = OUTBUFSIZ;
            Trace((stderr, "\ntransbufsiz = OUTBUFSIZ = %u\n",
                   (unsigned)OUTBUFSIZ));
#endif
        }
        if (G.newfile) {
#ifdef VMS_TEXT_CONV
            if (G.pInfo->hostnum == VMS_ && G.extra_field &&
                is_vms_varlen_txt(__G__ G.extra_field,
                                  G.lrec.extra_field_length))
                G.VMS_line_state = 0;
            else
                G.VMS_line_state = -1;
#endif
            G.didCRlast = FALSE;
            G.newfile = FALSE;
        }

#ifdef VMS_TEXT_CONV
        if (G.VMS_line_state >= 0)
        {
            p = rawbuf;
            q = transbuf;
            while ((extent)(p-rawbuf) < (extent)size) {
                switch (G.VMS_line_state) {


                    case 0:
                        G.VMS_line_length = 0;
                        if ((extent)(p-rawbuf) == (extent)size-1) {

                            G.VMS_line_length = (unsigned)(*p++);
                            G.VMS_line_state = 1;
                        } else {
                            G.VMS_line_length = makeword(p);
                            p += 2;
                            G.VMS_line_state = 2;
                        }
                        G.VMS_line_pad =
                               ((G.VMS_line_length & 1) != 0);
                        break;


                    case 1:
                        G.VMS_line_length += ((unsigned)(*p++) << 8);
                        G.VMS_line_state = 2;
                        break;


                    case 2:
                        {
                            extent remaining = (extent)size+(rawbuf-p);
                            extent outroom;

                            if (G.VMS_line_length < remaining) {
                                remaining = G.VMS_line_length;
                                G.VMS_line_state = 3;
                            }

                            outroom = transbuf+(extent)transbufsiz-q;
                            if (remaining >= outroom) {
                                remaining -= outroom;
                                for (;outroom > 0; p++, outroom--)
                                    *q++ = native(*p);
#ifdef DLL
                                if (G.redirect_data) {
                                    if (writeToMemory(__G__ transbuf,
                                          (extent)(q-transbuf))) return PK_ERR;
                                } else
#endif
                                if (!uO.cflag && WriteError(transbuf,
                                    (extent)(q-transbuf), G.outfile))
                                    return disk_error(__G);
                                else if (uO.cflag && (*G.message)((zvoid *)&G,
                                         transbuf, (ulg)(q-transbuf), 0))
                                    return PK_OK;
                                q = transbuf;

                            }
                            G.VMS_line_length -= remaining;
                            for (;remaining > 0; p++, remaining--)
                                *q++ = native(*p);
                        }
                        break;


                    case 3:
                        if (q > transbuf+(extent)transbufsiz-lenEOL) {
#ifdef DLL
                            if (G.redirect_data) {
                                if (writeToMemory(__G__ transbuf,
                                      (extent)(q-transbuf))) return PK_ERR;
                            } else
#endif
                            if (!uO.cflag &&
                                WriteError(transbuf, (extent)(q-transbuf),
                                  G.outfile))
                                return disk_error(__G);
                            else if (uO.cflag && (*G.message)((zvoid *)&G,
                                     transbuf, (ulg)(q-transbuf), 0))
                                return PK_OK;
                            q = transbuf;
                        }
                        PutNativeEOL
                        G.VMS_line_state = G.VMS_line_pad ? 4 : 0;
                        break;


                    case 4:
                        ++p;
                        G.VMS_line_state = 0;
                        break;
                }
            }

        } else
#endif


         {
            p = rawbuf;
            if (*p == LF && G.didCRlast)
                ++p;
            G.didCRlast = FALSE;
            for (q = transbuf;  (extent)(p-rawbuf) < (extent)size;  ++p) {
                if (*p == CR) {
                    PutNativeEOL
                    if ((extent)(p-rawbuf) == (extent)size-1)

                        G.didCRlast = TRUE;
                    else if (p[1] == LF)
                        ++p;
                } else if (*p == LF)
                    PutNativeEOL
                else
#ifndef DOS_FLX_OS2_W32
                if (*p != CTRLZ)
#endif
                    *q++ = native(*p);

#if (defined(SMALL_MEM) || defined(MED_MEM))
# if (lenEOL == 1)
                if (!unshrink)
# endif

                    if (q > transbuf+(extent)transbufsiz-lenEOL) {
                        Trace((stderr,
                          "p - rawbuf = %u   q-transbuf = %u   size = %lu\n",
                          (unsigned)(p-rawbuf), (unsigned)(q-transbuf), size));
                        if (!uO.cflag && WriteError(transbuf,
                            (extent)(q-transbuf), G.outfile))
                            return disk_error(__G);
                        else if (uO.cflag && (*G.message)((zvoid *)&G,
                                 transbuf, (ulg)(q-transbuf), 0))
                            return PK_OK;
                        q = transbuf;
                        continue;
                    }
#endif
            }
        }


        Trace((stderr, "p - rawbuf = %u   q-transbuf = %u   size = %lu\n",
          (unsigned)(p-rawbuf), (unsigned)(q-transbuf), size));
        if (q > transbuf) {
#ifdef DLL
            if (G.redirect_data) {
                if (writeToMemory(__G__ transbuf, (extent)(q-transbuf)))
                    return PK_ERR;
            } else
#endif
            if (!uO.cflag && WriteError(transbuf, (extent)(q-transbuf),
                G.outfile))
                return disk_error(__G);
            else if (uO.cflag && (*G.message)((zvoid *)&G, transbuf,
                (ulg)(q-transbuf), 0))
                return PK_OK;
        }
    }

    return PK_OK;

}
