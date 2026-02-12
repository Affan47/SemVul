SV *
Perl_parse_uniprop_string(pTHX_

    const char * const name,
    const Size_t name_len,
    const bool is_utf8,
    const bool to_fold,
    const bool runtime,
    const bool deferrable,
    bool *user_defined_ptr,
    SV * msg,
   const STRLEN level)
{
    dVAR;
    char* lookup_name;
    unsigned lookup_len;
    bool stricter = FALSE;

    bool is_nv_type = FALSE;

    unsigned int i, j = 0;
    int equals_pos = -1;
    int slash_pos  = -1;
    int table_index = 0;
    bool starts_with_In_or_Is = FALSE;
    Size_t lookup_offset = 0;
    Size_t non_pkg_begin = 0;
    bool could_be_user_defined = TRUE;
    SV * prop_definition = NULL;
    SV * fq_name = NULL;
    bool invert_return = FALSE;

    PERL_ARGS_ASSERT_PARSE_UNIPROP_STRING;

    Newx(lookup_name, name_len, char);
    SAVEFREEPV(lookup_name);

    for (i = 0; i < name_len; i++) {
        char cur = name[i];

        if (isIDCONT_A(cur)) {

            if (isUPPER_A(cur)) {
                lookup_name[j++] = toLOWER_A(cur);
                continue;
            }

            if (cur == '_') {
                continue;
            }

            lookup_name[j++] = cur;

            if (i - non_pkg_begin == 0 && ! isIDFIRST_A(cur)) {
                could_be_user_defined = FALSE;
            }

            continue;
        }

        if (cur == '-' || isSPACE_A(cur)) {
            could_be_user_defined = FALSE;
            continue;
        }

        if (    cur == '='
            || (cur == ':' && (i >= name_len - 1 || name[i+1] != ':')))
        {
            lookup_name[j++] = '=';
            equals_pos = j;
            could_be_user_defined = FALSE;
            break;
        }

        lookup_name[j++] = cur;

        if (cur == ':') {

            i++;
            non_pkg_begin = i + 1;
            lookup_name[j++] = ':';
        }
        else {
            could_be_user_defined = FALSE;
        }
    }

#define STRLENs(s)  (sizeof("" s "") - 1)

    if (non_pkg_begin == STRLENs("utf8::") && memBEGINPs(name, name_len, "utf8::")) {
        lookup_name +=  STRLENs("utf8::");
        j -=  STRLENs("utf8::");
        equals_pos -=  STRLENs("utf8::");
    }

    if (equals_pos >= 0) {
        assert(! stricter);

        i++;
        for (; i < name_len; i++) {
            if (! isSPACE_A(name[i])) {
                break;
            }
        }

        if (   isPUNCT_A(name[i])
            && name[i] != '-'
            && name[i] != '+'
            && name[i] != '_'
            && name[i] != '{')
        {

            table_index = match_uniprop((U8 *) lookup_name, j);
            if (table_index) {
                const char * const * prop_values
                                            = UNI_prop_value_ptrs[table_index];
                SV * subpattern;
                Size_t subpattern_len;
                REGEXP * subpattern_re;
                char open = name[i++];
                char close;
                const char * pos_in_brackets;
                bool escaped = 0;

                if (open == '\\') {
                    open = name[i++];
                    escaped = 1;
                }

                pos_in_brackets = strchr("([<)]>)]>", open);
                close = (pos_in_brackets) ? pos_in_brackets[3] : open;

                if (    i >= name_len
                    ||  name[name_len-1] != close
                    || (escaped && name[name_len-2] != '\\'))
                {
                    sv_catpvs(msg, "Unicode property wildcard not terminated");
                    goto append_name_to_msg;
                }

                Perl_ck_warner_d(aTHX_
                    packWARN(WARN_EXPERIMENTAL__UNIPROP_WILDCARDS),
                    "The Unicode property wildcards feature is experimental");

                subpattern_len = name_len - i - 1 - escaped;
                subpattern = Perl_newSVpvf(aTHX_ "(?iaa:%.*s)",
                                              (unsigned) subpattern_len,
                                              name + i);
                subpattern = sv_2mortal(subpattern);
                subpattern_re = re_compile(subpattern, 0);
                assert(subpattern_re);

                while (*prop_values) {
                    const char * const entry = *prop_values;
                    const Size_t len = strlen(entry);
                    SV* entry_sv = newSVpvn_flags(entry, len, SVs_TEMP);

                    if (pregexec(subpattern_re,
                                 (char *) entry,
                                 (char *) entry + len,
                                 (char *) entry, 0,
                                 entry_sv,
                                 0))
                    {
                        Size_t total_len = j + len;
                        SV * sub_invlist = NULL;
                        char * this_string;

                        Newxz(this_string, total_len + 1, char);
                        Copy(lookup_name, this_string, j, char);
                        my_strlcat(this_string, entry, total_len + 1);
                        SAVEFREEPV(this_string);
                        sub_invlist = parse_uniprop_string(this_string,
                                                           total_len,
                                                           is_utf8,
                                                           to_fold,
                                                           runtime,
                                                           deferrable,
                                                           user_defined_ptr,
                                                           msg,
                                                           level + 1);
                        _invlist_union(prop_definition, sub_invlist,
                                       &prop_definition);
                    }

                    prop_values++;
                }

                SvREFCNT_dec_NN(subpattern_re);

                if (prop_definition) {
                    return prop_definition;
                }

                sv_catpvs(msg, "No Unicode property value wildcard matches:");
                goto append_name_to_msg;
            }

        }

        if (memBEGINPs(lookup_name, j, "is")) {
            lookup_offset = 2;
        }

        is_nv_type = memEQs(lookup_name + lookup_offset,
                       j - 1 - lookup_offset, "numericvalue")
                  || memEQs(lookup_name + lookup_offset,
                      j - 1 - lookup_offset, "nv")
                  || (   memENDPs(lookup_name + lookup_offset,
                            j - 1 - lookup_offset, "numeric")
                      && (   memBEGINPs(lookup_name + lookup_offset,
                                      j - 1 - lookup_offset, "cjk")
                          || memBEGINPs(lookup_name + lookup_offset,
                                      j - 1 - lookup_offset, "k")));
        if (   is_nv_type
            || memEQs(lookup_name + lookup_offset,
                      j - 1 - lookup_offset, "canonicalcombiningclass")
            || memEQs(lookup_name + lookup_offset,
                      j - 1 - lookup_offset, "ccc")
            || memEQs(lookup_name + lookup_offset,
                      j - 1 - lookup_offset, "age")
            || memEQs(lookup_name + lookup_offset,
                      j - 1 - lookup_offset, "in")
            || memEQs(lookup_name + lookup_offset,
                      j - 1 - lookup_offset, "presentin"))
        {
            unsigned int k;

            stricter = TRUE;
            for (k = i; k < name_len; k++) {
                if (   isALPHA_A(name[k])
                    && (! is_nv_type || ! isALPHA_FOLD_EQ(name[k], 'E')))
                {
                    stricter = FALSE;
                    break;
                }
            }
        }

        if (stricter) {

            if (name[i] == '+') {
                i++;
            }
            else if (name[i] == '-') {
                lookup_name[j++] = '-';
                i++;
            }

            for (; i < name_len - 1; i++) {
                if (    name[i] != '0'
                    && (name[i] != '_' || ! isDIGIT_A(name[i+1])))
                {
                    break;
                }
            }
        }
    }
    else {

        if (   memBEGINPs(lookup_name, j, "perl")
            && memNEs(lookup_name + 4, j - 4, "space")
            && memNEs(lookup_name + 4, j - 4, "word"))
        {
            stricter = TRUE;

            i = j = 0;
        }
    }

    for (; i < name_len; i++) {
        char cur = name[i];

        if (isUPPER_A(cur)) {
            lookup_name[j++] = toLOWER(cur);
            continue;
        }

        if (cur == '_') {
            if (    stricter
                && (     i == 0 || (int) i == equals_pos || i == name_len- 1
                    || ! isDIGIT_A(name[i-1]) || ! isDIGIT_A(name[i+1])))
            {
                lookup_name[j++] = '_';
            }
            continue;
        }

        if (cur == '-' && ! stricter) {
            continue;
        }

        if (isSPACE_A(cur) && ! stricter) {
            continue;
        }

        lookup_name[j++] = cur;

        if (i >= name_len - 1 || cur != '/') {
            continue;
        }

        slash_pos = j;

        if (is_nv_type) {
            i++;
            if (i < name_len && name[i] == '+') {
                i++;
            }

            for (; i < name_len - 1; i++) {
                if (   name[i] != '0'
                    && (name[i] != '_' || ! isDIGIT_A(name[i+1])))
                {
                    break;
                }
            }

            lookup_name[j++] = name[i];
        }
    }

    if (  (   UNLIKELY(memEQs(lookup_name, j, "l"))
           || UNLIKELY(memEQs(lookup_name, j, "gc=l")))
        && UNLIKELY(name[name_len-1] == '_'))
    {
        lookup_name[j++] = '&';
    }

    if (    non_pkg_begin + name_len > 2
        &&  name[non_pkg_begin+0] == 'I'
        && (name[non_pkg_begin+1] == 'n' || name[non_pkg_begin+1] == 's'))
    {
        starts_with_In_or_Is = TRUE;
    }
    else {
        could_be_user_defined = FALSE;
    }

    if (could_be_user_defined) {
        CV* user_sub;

        bool empty_return = FALSE;

        user_sub = get_cvn_flags(name, name_len, 0);
        if (user_sub) {
            const char insecure[] = "Insecure user-defined property";

            dSP;
            SV * user_sub_sv = MUTABLE_SV(user_sub);
            SV * error;
            SV * key;
            SV * placeholder;
            SV ** saved_user_prop_ptr;

            PERL_INT_FAST8_T retry_countdown = 10;

            DECLARATION_FOR_GLOBAL_CONTEXT;

            *user_defined_ptr = TRUE;

            if (TAINT_get) {
                if (SvCUR(msg) > 0) sv_catpvs(msg, "; ");
                sv_catpvn(msg, insecure, sizeof(insecure) - 1);
                goto append_name_to_msg;
            }

            key = newSVpvn(((to_fold) ? "1" : "0"), 1);
            fq_name = S_get_fq_name(aTHX_ name, name_len, is_utf8,
                                          non_pkg_begin != 0);
            sv_catsv(key, fq_name);
            sv_2mortal(key);

          re_fetch:
            USER_PROP_MUTEX_LOCK;

            saved_user_prop_ptr = hv_fetch(PL_user_def_props,
                                                   SvPVX(key), SvCUR(key), 0);
            if (saved_user_prop_ptr) {

                if (is_invlist(*saved_user_prop_ptr)) {
                    prop_definition = *saved_user_prop_ptr;

                    USER_PROP_MUTEX_UNLOCK;

                    return prop_definition;
                }

                if (SvPOK(*saved_user_prop_ptr)) {
                    if (SvCUR(msg) > 0) sv_catpvs(msg, "; ");
                    sv_catsv(msg, *saved_user_prop_ptr);

                    USER_PROP_MUTEX_UNLOCK;

                    return NULL;
                }

                assert(SvIOK(*saved_user_prop_ptr));

                if (SvIV(*saved_user_prop_ptr) != PTR2IV(CUR_CONTEXT)) {

                    USER_PROP_MUTEX_UNLOCK;

                    if (retry_countdown-- > 0) {
                        PerlProc_sleep(1);
                        goto re_fetch;
                    }

                    if (SvCUR(msg) > 0) sv_catpvs(msg, "; ");
                    sv_catpvs(msg, "Timeout waiting for another thread to "
                                   "define");
                    goto append_name_to_msg;
                }

                USER_PROP_MUTEX_UNLOCK;

                if (SvCUR(msg) > 0) sv_catpvs(msg, "; ");
                sv_catpvs(msg,
                          "Infinite recursion in user-defined property");
                goto append_name_to_msg;
            }

            PUSHSTACKi(PERLSI_MAGIC);
            ENTER;

            SWITCH_TO_GLOBAL_CONTEXT;
            placeholder= newSVuv(PTR2IV(ORIGINAL_CONTEXT));
            (void) hv_store_ent(PL_user_def_props, key, placeholder, 0);
            RESTORE_CONTEXT;

            USER_PROP_MUTEX_UNLOCK;

            SAVEDESTRUCTOR_X(S_delete_recursion_entry, SvPVX(key));

            PUSHMARK(SP);
            SAVETMPS;

            XPUSHs(boolSV(to_fold));
            PUTBACK;

            SAVEHINTS();
            save_re_context();

            save_item(PL_subname);

            (void) call_sv(user_sub_sv, G_EVAL|G_SCALAR);

            SPAGAIN;

            error = ERRSV;
            if (TAINT_get || SvTRUE(error)) {
                if (SvCUR(msg) > 0) sv_catpvs(msg, "; ");
                if (SvTRUE(error)) {
                    sv_catpvs(msg, "Error \"");
                    sv_catsv(msg, error);
                    sv_catpvs(msg, "\"");
                }
                if (TAINT_get) {
                    if (SvTRUE(error)) sv_catpvs(msg, "; ");
                    sv_catpvn(msg, insecure, sizeof(insecure) - 1);
                }

                if (name_len > 0) {
                    sv_catpvs(msg, " in expansion of ");
                    Perl_sv_catpvf(aTHX_ msg, "%" UTF8f, UTF8fARG(is_utf8,
                                                                  name_len,
                                                                  name));
                }

                (void) POPs;
                prop_definition = NULL;
            }
            else {
                SV * contents = POPs;

                if (      deferrable
                    && (! SvPOK(contents) || SvCUR(contents) == 0))
                {
                        empty_return = TRUE;
                }
                else {

                    prop_definition = handle_user_defined_property(
                                                    name, name_len,
                                                    is_utf8, to_fold, runtime,
                                                    deferrable,
                                                    contents, user_defined_ptr,
                                                    msg,
                                                    level);
                }
            }

            USER_PROP_MUTEX_LOCK;

            S_delete_recursion_entry(aTHX_ SvPVX(key));

            if (    ! empty_return
                && (! prop_definition || is_invlist(prop_definition)))
            {

                SWITCH_TO_GLOBAL_CONTEXT;
                (void) hv_store_ent(PL_user_def_props,
                                    key,
                                    ((prop_definition)
                                     ? newSVsv(prop_definition)
                                     : newSVsv(msg)),
                                    0);
                RESTORE_CONTEXT;
            }

            USER_PROP_MUTEX_UNLOCK;

            FREETMPS;
            LEAVE;
            POPSTACK;

            if (empty_return) {
                goto definition_deferred;
            }

            if (prop_definition) {

                if (! is_invlist(prop_definition)) {
                    SvREFCNT_dec_NN(prop_definition);
                    goto definition_deferred;
                }

                sv_2mortal(prop_definition);
            }

            return prop_definition;

        }
    }

    lookup_len = j;

    table_index = match_uniprop((U8 *) lookup_name, lookup_len);

    if (table_index == 0) {

        if (starts_with_In_or_Is) {
            lookup_name += 2;
            lookup_len -= 2;
            equals_pos -= 2;
            slash_pos -= 2;

            table_index = match_uniprop((U8 *) lookup_name, lookup_len);
        }

        if (table_index == 0) {
            char * canonical;

            if (! is_nv_type) {
                if (! could_be_user_defined) {
                    goto failed;
                }

                if (! deferrable) {
                    if (SvCUR(msg) > 0) sv_catpvs(msg, "; ");
                    sv_catpvs(msg, "Unknown user-defined property name");
                    goto append_name_to_msg;
                }

                goto definition_deferred;
            }

            if (slash_pos < 0) {

                NV value;
                SSize_t value_len = lookup_len - equals_pos;

                if (   value_len <= 0
                    || my_atof3(lookup_name + equals_pos, &value,
                                value_len)
                          != lookup_name + lookup_len)
                {
                    goto failed;
                }

                if (Perl_ceil(value) == value) {
                    canonical = Perl_form(aTHX_ "%.*s%.0" NVff,
                                            equals_pos, lookup_name, value);
                }
                else {
                    char * exp_ptr;

                    canonical = Perl_form(aTHX_ "%.*s%.*" NVef,
                                                equals_pos, lookup_name,
                                                PL_E_FORMAT_PRECISION, value);

                    exp_ptr = strchr(canonical + equals_pos, 'e');
                    if (exp_ptr) {
                        char * cur_ptr = exp_ptr + 2;
                        SSize_t excess_exponent_len = strlen(cur_ptr) - 2;

                        assert(*(cur_ptr - 1) == '-' || *(cur_ptr - 1) == '+');

                        if (excess_exponent_len > 0) {
                            SSize_t leading_zeros = strspn(cur_ptr, "0");
                            SSize_t excess_leading_zeros
                                    = MIN(leading_zeros, excess_exponent_len);
                            if (excess_leading_zeros > 0) {
                                Move(cur_ptr + excess_leading_zeros,
                                     cur_ptr,
                                     strlen(cur_ptr) - excess_leading_zeros
                                       + 1,
                                     char);
                            }
                        }
                    }
                }
            }
            else {
                UV numerator, denominator, gcd, trial;
                const char * end_ptr;
                const char * sign = "";

                const char * this_lookup_name = lookup_name + equals_pos;
                lookup_len -= equals_pos;
                slash_pos -= equals_pos;

                if (this_lookup_name[0] == '-') {
                    sign = "-";
                    this_lookup_name++;
                    lookup_len--;
                    slash_pos--;
                }

                end_ptr = this_lookup_name + slash_pos;
                if (! grok_atoUV(this_lookup_name, &numerator, &end_ptr)) {
                    goto failed;
                }

                if (*end_ptr != '/') {
                    goto failed;
                }

                this_lookup_name += slash_pos;
                lookup_len -= slash_pos;
                end_ptr = this_lookup_name + lookup_len;

                if (! grok_atoUV(this_lookup_name, &denominator, &end_ptr)) {
                    goto failed;
                }

                if (   end_ptr != this_lookup_name + lookup_len
                    || denominator == 0)
                {
                    goto failed;
                }

                gcd = numerator;
                trial = denominator;
                while (trial != 0) {
                    UV temp = trial;
                    trial = gcd % trial;
                    gcd = temp;
                }

                if (gcd == 1) {
                    goto failed;
                }

                numerator /= gcd;
                denominator /= gcd;

                canonical = Perl_form(aTHX_ "%.*s%s%" UVuf "/%" UVuf,
                        equals_pos, lookup_name, sign, numerator, denominator);
            }

            table_index = match_uniprop((U8 *) canonical, strlen(canonical));
            if (table_index == 0) {
                goto failed;
            }
        }
    }

    if (table_index < 0) {
        invert_return = TRUE;
        table_index = -table_index;
    }

    if (table_index > MAX_UNI_KEYWORD_INDEX) {
        Size_t warning_offset = table_index / MAX_UNI_KEYWORD_INDEX;
        table_index %= MAX_UNI_KEYWORD_INDEX;
        Perl_ck_warner_d(aTHX_ packWARN(WARN_DEPRECATED),
                "Use of '%.*s' in \\p{} or \\P{} is deprecated because: %s",
                (int) name_len, name, deprecated_property_msgs[warning_offset]);
    }

    if (to_fold) {
        if (   table_index == UNI_XPOSIXUPPER
            || table_index == UNI_XPOSIXLOWER
            || table_index == UNI_TITLE)
        {
            table_index = UNI_CASED;
        }
        else if (   table_index == UNI_UPPERCASELETTER
                 || table_index == UNI_LOWERCASELETTER
#  ifdef UNI_TITLECASELETTER
                 || table_index == UNI_TITLECASELETTER
#  endif
        ) {
            table_index = UNI_CASEDLETTER;
        }
        else if (  table_index == UNI_POSIXUPPER
                || table_index == UNI_POSIXLOWER)
        {
            table_index = UNI_POSIXALPHA;
        }
    }

    prop_definition =_new_invlist_C_array(uni_prop_ptrs[table_index]);
    sv_2mortal(prop_definition);

    {
        COPHH * hinthash = (IN_PERL_COMPILETIME)
                           ? CopHINTHASH_get(&PL_compiling)
                           : CopHINTHASH_get(PL_curcop);
	SV * pu_overrides = cophh_fetch_pv(hinthash, "private_use", 0, 0);

        if (UNLIKELY(pu_overrides && SvPOK(pu_overrides))) {

            SV * pu_lookup = Perl_newSVpvf(aTHX_ "%d=", table_index);
            const char * pos = strstr(SvPVX(pu_overrides), SvPVX(pu_lookup));

            if (pos) {
                bool dummy;
                SV * pu_definition;
                SV * pu_invlist;
                SV * expanded_prop_definition =
                            sv_2mortal(invlist_clone(prop_definition, NULL));

                pos += SvCUR(pu_lookup);
                pu_definition = newSVpvn(pos, strchr(pos, '\a') - pos);
                pu_invlist = handle_user_defined_property(lookup_name,
                                                          lookup_len,
                                                          0,
                                                          0,
                                                          runtime,
                                                          deferrable,
                                                          pu_definition,
                                                          &dummy,
                                                          msg,
                                                          level);
                if (TAINT_get) {
                    if (SvCUR(msg) > 0) sv_catpvs(msg, "; ");
                    sv_catpvs(msg, "Insecure private-use override");
                    goto append_name_to_msg;
                }

                _invlist_intersection(pu_invlist, PL_Private_Use, &pu_invlist);

                _invlist_union(prop_definition, pu_invlist,
                               &expanded_prop_definition);
                prop_definition = expanded_prop_definition;
                Perl_ck_warner_d(aTHX_ packWARN(WARN_EXPERIMENTAL__PRIVATE_USE), "The private_use feature is experimental");
            }
        }
    }

    if (invert_return) {
        _invlist_invert(prop_definition);
    }
    return prop_definition;

  failed:
    if (non_pkg_begin != 0) {
        if (SvCUR(msg) > 0) sv_catpvs(msg, "; ");
        sv_catpvs(msg, "Illegal user-defined property name");
    }
    else {
        if (SvCUR(msg) > 0) sv_catpvs(msg, "; ");
        sv_catpvs(msg, "Can't find Unicode property definition");
    }

  append_name_to_msg:
    {
        const char * prefix = (runtime && level == 0) ?  " \\p{" : " \"";
        const char * suffix = (runtime && level == 0) ?  "}" : "\"";

        sv_catpv(msg, prefix);
        Perl_sv_catpvf(aTHX_ msg, "%" UTF8f, UTF8fARG(is_utf8, name_len, name));
        sv_catpv(msg, suffix);
    }

    return NULL;

  definition_deferred:

    if (! fq_name) {
        fq_name = S_get_fq_name(aTHX_ name, name_len, is_utf8,
                                      non_pkg_begin != 0
                               );
    }
    sv_catpvs(fq_name, "\n");

    *user_defined_ptr = TRUE;
    return fq_name;
}
}
