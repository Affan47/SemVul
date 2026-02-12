STATIC int
S_handle_possible_posix(pTHX_ RExC_state_t *pRExC_state,

    const char * const s,


    char ** updated_parse_ptr,

    AV ** posix_warnings,

    const bool check_only
)
{


    const char* p             = s;
    const char * const e      = RExC_end;
    unsigned complement       = 0;
    bool found_problem        = FALSE;
    bool has_opening_bracket  = FALSE;
    bool has_opening_colon    = FALSE;
    int class_number          = OOB_NAMEDCLASS;

    const char * possible_end = NULL;
    const char* name_start;


    int max_distance          = 2;


    UV input_text[15];
    STATIC_ASSERT_DECL(C_ARRAY_LENGTH(input_text) >= sizeof "alphanumeric");

    PERL_ARGS_ASSERT_HANDLE_POSSIBLE_POSIX;

    CLEAR_POSIX_WARNINGS();

    if (p >= e) {
        return NOT_MEANT_TO_BE_A_POSIX_CLASS;
    }

    if (*(p - 1) != '[') {
        ADD_POSIX_WARNING(p, "it doesn't start with a '['");
        found_problem = TRUE;
    }
    else {
        has_opening_bracket = TRUE;
    }


    if (isBLANK(*p)) {
        found_problem = TRUE;

        do {
            p++;
        } while (p < e && isBLANK(*p));

        ADD_POSIX_WARNING(p, NO_BLANKS_POSIX_WARNING);
    }


    if (POSIXCC_NOTYET(*p) && p < e - 3)


    {
        const char open_char  = *p;
        const char * temp_ptr = p + 1;


        if (temp_ptr[1] == open_char) {
            temp_ptr++;
        }
        else while (    temp_ptr < e
                    && (isWORDCHAR(*temp_ptr) || *temp_ptr == '-'))
        {
            temp_ptr++;
        }

        if (*temp_ptr == open_char) {
            temp_ptr++;
            if (*temp_ptr == ']') {
                temp_ptr++;
                if (! found_problem && ! check_only) {
                    RExC_parse = (char *) temp_ptr;
                    vFAIL3("POSIX syntax [%c %c] is reserved for future "
                            "extensions", open_char, open_char);
                }


                if (updated_parse_ptr) {
                    *updated_parse_ptr = (char *) temp_ptr;
                }

                CLEAR_POSIX_WARNINGS_AND_RETURN(OOB_NAMEDCLASS);
            }
        }


    }


    if (*p == '^') {
        found_problem = TRUE;
        ADD_POSIX_WARNING(p + 1, "the '^' must come after the colon");
        complement = 1;
        p++;

        if (isBLANK(*p)) {
            found_problem = TRUE;

            do {
                p++;
            } while (p < e && isBLANK(*p));

            ADD_POSIX_WARNING(p, NO_BLANKS_POSIX_WARNING);
        }
    }


    if (*p == ':') {
        p++;
        has_opening_colon = TRUE;
    }
    else if (*p == ';') {
        found_problem = TRUE;
        p++;
        ADD_POSIX_WARNING(p, SEMI_COLON_POSIX_WARNING);
        has_opening_colon = TRUE;
    }
    else {
        found_problem = TRUE;
        ADD_POSIX_WARNING(p, "there must be a starting ':'");


        if (*p != '^' && *p != ']' && isPUNCT(*p)) {
            p++;
        }
    }


    if (isBLANK(*p)) {
        found_problem = TRUE;

        do {
            p++;
        } while (p < e && isBLANK(*p));

        ADD_POSIX_WARNING(p, NO_BLANKS_POSIX_WARNING);
    }

    if (*p == '^') {


        if (complement) {
            CLEAR_POSIX_WARNINGS_AND_RETURN(NOT_MEANT_TO_BE_A_POSIX_CLASS);
        }

        complement = 1;
        p++;
    }


    if (isBLANK(*p)) {
        found_problem = TRUE;

        do {
            p++;
        } while (p < e && isBLANK(*p));

        ADD_POSIX_WARNING(p, NO_BLANKS_POSIX_WARNING);
    }

    if (*p == ']') {


        if (has_opening_bracket) {
            CLEAR_POSIX_WARNINGS_AND_RETURN(NOT_MEANT_TO_BE_A_POSIX_CLASS);
        }


        p--;

        if (*p == ';') {
            found_problem = TRUE;
            ADD_POSIX_WARNING(p, SEMI_COLON_POSIX_WARNING);
        }
        else if (*p != ':') {


            CLEAR_POSIX_WARNINGS_AND_RETURN(NOT_MEANT_TO_BE_A_POSIX_CLASS);
        }


        has_opening_colon = FALSE;
        p--;

        while (p > RExC_start && isWORDCHAR(*p)) {
            p--;
        }
        p++;


    }


    name_start = p;
  parse_name:
    {
        bool has_blank               = FALSE;
        bool has_upper               = FALSE;
        bool has_terminating_colon   = FALSE;
        bool has_terminating_bracket = FALSE;
        bool has_semi_colon          = FALSE;
        unsigned int name_len        = 0;
        int punct_count              = 0;

        while (p < e) {


            if (isBLANK(*p) ) {
                has_blank = TRUE;
                found_problem = TRUE;
                p++;
                continue;
            }


            if (isPUNCT(*p)) {
                const char * peek = p + 1;


                if (*p != ']') {
                    if (peek < e && isBLANK(*peek)) {
                        has_blank = TRUE;
                        found_problem = TRUE;
                        do {
                            peek++;
                        } while (peek < e && isBLANK(*peek));
                    }

                    if (peek < e && *peek == ']') {
                        has_terminating_bracket = TRUE;
                        if (*p == ':') {
                            has_terminating_colon = TRUE;
                        }
                        else if (*p == ';') {
                            has_semi_colon = TRUE;
                            has_terminating_colon = TRUE;
                        }
                        else {
                            found_problem = TRUE;
                        }
                        p = peek + 1;
                        goto try_posix;
                    }
                }


                if (*p == ']' || *p == '[' || *p == ':' || *p == ';') {


                    if (possible_end) {
                        break;
                    }
                    possible_end = p;
                }


                if (++punct_count > max_distance) {
                    break;
                }


                input_text[name_len++] = *p;
                p++;
            }
            else if (isUPPER(*p)) {
                input_text[name_len++] = toLOWER(*p);
                has_upper = TRUE;
                found_problem = TRUE;
                p++;
            } else if (! UTF || UTF8_IS_INVARIANT(*p)) {
                input_text[name_len++] = *p;
                p++;
            }
            else {
                input_text[name_len++] = utf8_to_uvchr_buf((U8 *) p, e, NULL);
                p+= UTF8SKIP(p);
            }


            if (name_len >= C_ARRAY_LENGTH(input_text)) {
                break;
            }
        }


        found_problem = TRUE;


        if (   name_len >= C_ARRAY_LENGTH(input_text)
            || punct_count > max_distance)
        {


            if (possible_end && possible_end != (char *) -1) {
                possible_end = (char *) -1;

                p = name_start;
                goto parse_name;
            }


            CLEAR_POSIX_WARNINGS_AND_RETURN(NOT_MEANT_TO_BE_A_POSIX_CLASS);
        }


        if (name_len && p == e && isPUNCT(*(p-1))) {
            p--;
            name_len--;
        }

        if (p < e && isPUNCT(*p)) {
            if (*p == ']') {
                has_terminating_bracket = TRUE;


                if (   possible_end
                    && possible_end != (char *) -1
                    && *possible_end == ']'
                    && name_len && input_text[name_len - 1] == ']')
                {
                    name_len--;
                    p = possible_end;


                    possible_end = (char *) -1;
                }
            }
            else {
                if (*p == ':') {
                    has_terminating_colon = TRUE;
                }
                else if (*p == ';') {
                    has_semi_colon = TRUE;
                    has_terminating_colon = TRUE;
                }
                p++;
            }
        }

    try_posix:


        if (name_len < 3) {
            CLEAR_POSIX_WARNINGS_AND_RETURN(NOT_MEANT_TO_BE_A_POSIX_CLASS);
        }


        switch (name_len) {
            case 4:
                if (memEQs(name_start, 4, "word")) {

                    class_number = ANYOF_WORDCHAR;
                }
                break;
            case 5:


                switch (name_start[4]) {
                    case 'a':
                        if (memBEGINs(name_start, 5, "alph"))
                            class_number = ANYOF_ALPHA;
                        break;
                    case 'e':
                        if (memBEGINs(name_start, 5, "spac"))
                            class_number = ANYOF_SPACE;
                        break;
                    case 'h':
                        if (memBEGINs(name_start, 5, "grap"))
                            class_number = ANYOF_GRAPH;
                        break;
                    case 'i':
                        if (memBEGINs(name_start, 5, "asci"))
                            class_number = ANYOF_ASCII;
                        break;
                    case 'k':
                        if (memBEGINs(name_start, 5, "blan"))
                            class_number = ANYOF_BLANK;
                        break;
                    case 'l':
                        if (memBEGINs(name_start, 5, "cntr"))
                            class_number = ANYOF_CNTRL;
                        break;
                    case 'm':
                        if (memBEGINs(name_start, 5, "alnu"))
                            class_number = ANYOF_ALPHANUMERIC;
                        break;
                    case 'r':
                        if (memBEGINs(name_start, 5, "lowe"))
                            class_number = (FOLD) ? ANYOF_CASED : ANYOF_LOWER;
                        else if (memBEGINs(name_start, 5, "uppe"))
                            class_number = (FOLD) ? ANYOF_CASED : ANYOF_UPPER;
                        break;
                    case 't':
                        if (memBEGINs(name_start, 5, "digi"))
                            class_number = ANYOF_DIGIT;
                        else if (memBEGINs(name_start, 5, "prin"))
                            class_number = ANYOF_PRINT;
                        else if (memBEGINs(name_start, 5, "punc"))
                            class_number = ANYOF_PUNCT;
                        break;
                }
                break;
            case 6:
                if (memEQs(name_start, 6, "xdigit"))
                    class_number = ANYOF_XDIGIT;
                break;
        }


        if (class_number == OOB_NAMEDCLASS && found_problem) {
            const UV posix_names[][6] = {
                                                { 'a', 'l', 'n', 'u', 'm' },
                                                { 'a', 'l', 'p', 'h', 'a' },
                                                { 'a', 's', 'c', 'i', 'i' },
                                                { 'b', 'l', 'a', 'n', 'k' },
                                                { 'c', 'n', 't', 'r', 'l' },
                                                { 'd', 'i', 'g', 'i', 't' },
                                                { 'g', 'r', 'a', 'p', 'h' },
                                                { 'l', 'o', 'w', 'e', 'r' },
                                                { 'p', 'r', 'i', 'n', 't' },
                                                { 'p', 'u', 'n', 'c', 't' },
                                                { 's', 'p', 'a', 'c', 'e' },
                                                { 'u', 'p', 'p', 'e', 'r' },
                                                { 'w', 'o', 'r', 'd' },
                                                { 'x', 'd', 'i', 'g', 'i', 't' }
                                            };


            const UV posix_name_lengths[] = {
                                                sizeof("alnum") - 1,
                                                sizeof("alpha") - 1,
                                                sizeof("ascii") - 1,
                                                sizeof("blank") - 1,
                                                sizeof("cntrl") - 1,
                                                sizeof("digit") - 1,
                                                sizeof("graph") - 1,
                                                sizeof("lower") - 1,
                                                sizeof("print") - 1,
                                                sizeof("punct") - 1,
                                                sizeof("space") - 1,
                                                sizeof("upper") - 1,
                                                sizeof("word")  - 1,
                                                sizeof("xdigit")- 1
                                            };
            unsigned int i;
            int temp_max = max_distance;


            if (   has_opening_bracket + has_opening_colon < 2
                || has_terminating_bracket + has_terminating_colon < 2)
            {
                temp_max--;
            }


            for (i = 0; i < C_ARRAY_LENGTH(posix_names); i++) {


                if (abs( (int) (name_len - posix_name_lengths[i]))
                    > temp_max)
                {
                    continue;
                }

                if (edit_distance(input_text,
                                  posix_names[i],
                                  name_len,
                                  posix_name_lengths[i],
                                  temp_max
                                 )
                    > -1)
                {
                    goto probably_meant_to_be;
                }
            }


            if (possible_end && possible_end != (char *) -1) {
                possible_end = (char *) -1;
                p = name_start;
                goto parse_name;
            }


            CLEAR_POSIX_WARNINGS_AND_RETURN(NOT_MEANT_TO_BE_A_POSIX_CLASS);
        }

    probably_meant_to_be:


        if (updated_parse_ptr) {
            *updated_parse_ptr = (char *) p;
        }


        if (found_problem) {


            if (has_upper) {
                ADD_POSIX_WARNING(p, "the name must be all lowercase letters");
            }
            if (has_blank) {
                ADD_POSIX_WARNING(p, NO_BLANKS_POSIX_WARNING);
            }
            if (has_semi_colon) {
                ADD_POSIX_WARNING(p, SEMI_COLON_POSIX_WARNING);
            }
            else if (! has_terminating_colon) {
                ADD_POSIX_WARNING(p, "there is no terminating ':'");
            }
            if (! has_terminating_bracket) {
                ADD_POSIX_WARNING(p, "there is no terminating ']'");
            }

            if (   posix_warnings
                && RExC_warn_text
                && av_top_index(RExC_warn_text) > -1)
            {
                *posix_warnings = RExC_warn_text;
            }
        }
        else if (class_number != OOB_NAMEDCLASS) {


            CLEAR_POSIX_WARNINGS_AND_RETURN(class_number + complement);
        }
        else if (! check_only) {


            const char * const complement_string = (complement)
                                                   ? "^"
                                                   : "";
            RExC_parse = (char *) p;
            vFAIL3utf8f("POSIX class [:%s%" UTF8f ":] unknown",
                        complement_string,
                        UTF8fARG(UTF, RExC_parse - name_start - 2, name_start));
        }
    }

    return OOB_NAMEDCLASS;
}
