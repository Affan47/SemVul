HttpHeader::parse(const char *header_start, size_t hdrLen)
{
    const char *field_ptr = header_start;
    const char *header_end = header_start + hdrLen;
    int warnOnError = (Config.onoff.relaxed_header_parser <= 0 ? DBG_IMPORTANT : 2);

    PROF_start(HttpHeaderParse);

    assert(header_start && header_end);
    debugs(55, 7, "parsing hdr: (" << this << ")" << std::endl << getStringPrefix(header_start, hdrLen));
    ++ HttpHeaderStats[owner].parsedCount;

    char *nulpos;
    if ((nulpos = (char*)memchr(header_start, '\0', hdrLen))) {
        debugs(55, DBG_IMPORTANT, "WARNING: HTTP header contains NULL characters {" <<
               getStringPrefix(header_start, nulpos-header_start) << "}\nNULL\n{" << getStringPrefix(nulpos+1, hdrLen-(nulpos-header_start)-1));
        PROF_stop(HttpHeaderParse);
        clean();
        return 0;
    }

    Http::ContentLengthInterpreter clen(warnOnError);

    while (field_ptr < header_end) {
        const char *field_start = field_ptr;
        const char *field_end;

        const char *hasBareCr = nullptr;
        size_t lines = 0;
        do {
            const char *this_line = field_ptr;
            field_ptr = (const char *)memchr(field_ptr, '\n', header_end - field_ptr);
            ++lines;

            if (!field_ptr) {

                PROF_stop(HttpHeaderParse);
                clean();
                return 0;
            }

            field_end = field_ptr;

            ++field_ptr;

            if (field_end > this_line && field_end[-1] == '\r') {
                --field_end;

                if (owner == hoRequest && field_end > this_line) {
                    bool cr_only = true;
                    for (const char *p = this_line; p < field_end && cr_only; ++p) {
                        if (*p != '\r')
                            cr_only = false;
                    }
                    if (cr_only) {
                        debugs(55, DBG_IMPORTANT, "SECURITY WARNING: Rejecting HTTP request with a CR+ "
                               "header field to prevent request smuggling attacks: {" <<
                               getStringPrefix(header_start, hdrLen) << "}");
                        PROF_stop(HttpHeaderParse);
                        clean();
                        return 0;
                    }
                }
            }

            if (memchr(this_line, '\r', field_end - this_line)) {
                hasBareCr = "bare CR";
                debugs(55, warnOnError, "WARNING: suspicious CR characters in HTTP header {" <<
                       getStringPrefix(field_start, field_end-field_start) << "}");

                if (Config.onoff.relaxed_header_parser) {
                    char *p = (char *) this_line;

                    while ((p = (char *)memchr(p, '\r', field_end - p)) != NULL) {
                        *p = ' ';
                        ++p;
                    }
                } else {
                    PROF_stop(HttpHeaderParse);
                    clean();
                    return 0;
                }
            }

            if (this_line + 1 == field_end && this_line > field_start) {
                debugs(55, warnOnError, "WARNING: Blank continuation line in HTTP header {" <<
                       getStringPrefix(header_start, hdrLen) << "}");
                PROF_stop(HttpHeaderParse);
                clean();
                return 0;
            }
        } while (field_ptr < header_end && (*field_ptr == ' ' || *field_ptr == '\t'));

        if (field_start == field_end) {
            if (field_ptr < header_end) {
                debugs(55, warnOnError, "WARNING: unparseable HTTP header field near {" <<
                       getStringPrefix(field_start, hdrLen-(field_start-header_start)) << "}");
                PROF_stop(HttpHeaderParse);
                clean();
                return 0;
            }

            break;
        }

        const auto e = HttpHeaderEntry::parse(field_start, field_end, owner);
        if (!e) {
            debugs(55, warnOnError, "WARNING: unparseable HTTP header field {" <<
                   getStringPrefix(field_start, field_end-field_start) << "}");
            debugs(55, warnOnError, " in {" << getStringPrefix(header_start, hdrLen) << "}");

            PROF_stop(HttpHeaderParse);
            clean();
            return 0;
        }

        if (lines > 1 || hasBareCr) {
            const auto framingHeader = (e->id == Http::HdrType::CONTENT_LENGTH || e->id == Http::HdrType::TRANSFER_ENCODING);
            if (framingHeader) {
                if (!hasBareCr)
                    debugs(55, warnOnError, "WARNING: obs-fold in framing-sensitive " << e->name << ": " << e->value);
                delete e;
                PROF_stop(HttpHeaderParse);
                clean();
                return 0;
            }
        }

        if (e->id == Http::HdrType::CONTENT_LENGTH && !clen.checkField(e->value)) {
            delete e;

            if (Config.onoff.relaxed_header_parser)
                continue;

            PROF_stop(HttpHeaderParse);
            clean();
            return 0;
        }

        addEntry(e);
    }

    if (clen.headerWideProblem) {
        debugs(55, warnOnError, "WARNING: " << clen.headerWideProblem <<
               " Content-Length field values in" <<
               Raw("header", header_start, hdrLen));
    }

    String rawTe;
    if (getByIdIfPresent(Http::HdrType::TRANSFER_ENCODING, &rawTe)) {

        delById(Http::HdrType::CONTENT_LENGTH);

        if (rawTe == "chunked") {
            ;
        } else if (rawTe == "identity") {
            delById(Http::HdrType::TRANSFER_ENCODING);
        } else {

            debugs(55, warnOnError, "WARNING: unsupported Transfer-Encoding used by client: " << rawTe);
            teUnsupported_ = true;
        }

    } else if (clen.sawBad) {

        delById(Http::HdrType::CONTENT_LENGTH);
        conflictingContentLength_ = true;
    } else if (clen.needsSanitizing) {

        delById(Http::HdrType::CONTENT_LENGTH);
        if (clen.sawGood) {
            putInt64(Http::HdrType::CONTENT_LENGTH, clen.value);
            debugs(55, 5, "sanitized Content-Length to be " << clen.value);
        }
    }

    PROF_stop(HttpHeaderParse);
    return 1;
}
}
