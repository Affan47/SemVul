SV *
Perl_handle_user_defined_property(pTHX_


    const char * name,
    const STRLEN name_len,
    const bool is_utf8,
    const bool to_fold,
    const bool runtime,
    const bool deferrable,

    SV* contents,
    bool *user_defined_ptr,


    SV * msg,

    const STRLEN level)
{
    STRLEN len;
    const char * string         = SvPV_const(contents, len);
    const char * const e        = string + len;
    const bool is_contents_utf8 = cBOOL(SvUTF8(contents));
    const STRLEN msgs_length_on_entry = SvCUR(msg);

    const char * s0 = string;

    const char overflow_msg[] = "Code point too large in \"";
    SV* running_definition = NULL;

    PERL_ARGS_ASSERT_HANDLE_USER_DEFINED_PROPERTY;

    *user_defined_ptr = TRUE;


    while (s0 < e) {
        const char * s;
        char op = '+';
        IV   min = 0;
        IV   max = -1;
        SV* this_definition;


        if (*s0 == '#') {
            s0 = strchr(s0, '\n');
            if (s0 == NULL) {
                break;
            }
            s0++;
            continue;
        }


        if (*s0 == '\n') {
            s0++;
            continue;
        }


        if (   *s0 == '+'
            || *s0 == '!'
            || *s0 == '-'
            || *s0 == '&')
        {
            op = *s0++;
        }


        s = s0;

        if (! isXDIGIT(*s)) {
            goto check_if_property;
        }

        do {
            if (min > ( (IV) MAX_LEGAL_CP >> 4)) {
                s = strchr(s, '\n');
                if (s == NULL) {
                    s = e;
                }
                if (SvCUR(msg) > 0) sv_catpvs(msg, "; ");
                sv_catpv(msg, overflow_msg);
                Perl_sv_catpvf(aTHX_ msg, "%" UTF8f,
                                     UTF8fARG(is_contents_utf8, s - s0, s0));
                sv_catpvs(msg, "\"");
                goto return_failure;
            }


            min = (min << 4) + READ_XDIGIT(s);
        } while (isXDIGIT(*s));

        while (isBLANK(*s)) { s++; }


        if (*s == '#') {
            s = strchr(s, '\n');
            if (s == NULL) {
                s = e;
            }
            s++;
        }
        else if (s < e && *s != '\n') {
            if (! isXDIGIT(*s)) {
                goto check_if_property;
            }


            max = 0;
            do {
                if (max > ( (IV) MAX_LEGAL_CP >> 4)) {
                    s = strchr(s, '\n');
                    if (s == NULL) {
                        s = e;
                    }
                    if (SvCUR(msg) > 0) sv_catpvs(msg, "; ");
                    sv_catpv(msg, overflow_msg);
                    Perl_sv_catpvf(aTHX_ msg, "%" UTF8f,
                                      UTF8fARG(is_contents_utf8, s - s0, s0));
                    sv_catpvs(msg, "\"");
                    goto return_failure;
                }

                max = (max << 4) + READ_XDIGIT(s);
            } while (isXDIGIT(*s));

            while (isBLANK(*s)) { s++; }

            if (*s == '#') {
                s = strchr(s, '\n');
                if (s == NULL) {
                    s = e;
                }
            }
            else if (s < e && *s != '\n') {
                goto check_if_property;
            }
        }

        if (max == -1) {
            max = min;
        }
        else if (max < min) {
            if (SvCUR(msg) > 0) sv_catpvs(msg, "; ");
            sv_catpvs(msg, "Illegal range in \"");
            Perl_sv_catpvf(aTHX_ msg, "%" UTF8f,
                                UTF8fARG(is_contents_utf8, s - s0, s0));
            sv_catpvs(msg, "\"");
            goto return_failure;
        }

#if 0

        if (   UNICODE_IS_PERL_EXTENDED(min)
            || UNICODE_IS_PERL_EXTENDED(max))
        {
            if (SvCUR(msg) > 0) sv_catpvs(msg, "; ");


            sv_catpv(msg, get_extended_utf8_msg(
                                            (UNICODE_IS_PERL_EXTENDED(min))
                                            ? min : max));
            sv_catpvs(msg, " in \"");
            Perl_sv_catpvf(aTHX_ msg, "%" UTF8f,
                                 UTF8fARG(is_contents_utf8, s - s0, s0));
            sv_catpvs(msg, "\"");
        }

#endif


        this_definition = sv_2mortal(_new_invlist(2));
        this_definition = _add_range_to_invlist(this_definition, min, max);
        goto calculate;

      check_if_property:


        s = strpbrk(s, "#\n");
        if (s == NULL) {
            s = e;
        }


        s--;
        while (s > s0 && isBLANK_A(*s)) {
            s--;
        }
        s++;

        this_definition = parse_uniprop_string(s0, s - s0,
                                               is_utf8, to_fold, runtime,
                                               deferrable,
                                               user_defined_ptr, msg,
                                               (name_len == 0)
                                                ? level

                                                : level + 1
                                              );
        if (this_definition == NULL) {
            goto return_failure;

        }

        if (! is_invlist(this_definition)) {
            return newSVsv(this_definition);
        }

        if (*s != '\n') {
            s = strchr(s, '\n');
            if (s == NULL) {
                s = e;
            }
        }

      calculate:

        switch (op) {
            case '+':
                _invlist_union(running_definition, this_definition,
                                                        &running_definition);
                break;
            case '-':
                _invlist_subtract(running_definition, this_definition,
                                                        &running_definition);
                break;
            case '&':
                _invlist_intersection(running_definition, this_definition,
                                                        &running_definition);
                break;
            case '!':
                _invlist_union_complement_2nd(running_definition,
                                        this_definition, &running_definition);
                break;
            default:
                Perl_croak(aTHX_ "panic: %s: %d: Unexpected operation %d",
                                 __FILE__, __LINE__, op);
                break;
        }


        s0 = s + 1;
    }


    if (msgs_length_on_entry == SvCUR(msg)) {


        if (running_definition == NULL) {
            running_definition = _new_invlist(1);
        }

        return running_definition;
    }


    goto return_msg;

  return_failure:
    running_definition = NULL;

  return_msg:

    if (name_len > 0) {
        sv_catpvs(msg, " in expansion of ");
        Perl_sv_catpvf(aTHX_ msg, "%" UTF8f, UTF8fARG(is_utf8, name_len, name));
    }

    return running_definition;
}
