STATIC void
S_put_range(pTHX_ SV *sv, UV start, const UV end, const bool allow_literals)
{


    const unsigned int min_range_count = 3;

    assert(start <= end);

    PERL_ARGS_ASSERT_PUT_RANGE;

    while (start <= end) {
        UV this_end;
        const char * format;

        if (end - start < min_range_count) {


            for (; start <= end; start++) {
                put_code_point(sv, start);
            }
            break;
        }


        if (allow_literals && start <= MAX_PRINT_A) {


            if (! isPRINT_A(start)) {
                UV temp_end = start + 1;


                UV max = MIN(end, MAX_PRINT_A);

                while (temp_end <= max && ! isPRINT_A(temp_end)) {
                    temp_end++;
                }


                if (temp_end > MAX_PRINT_A) {
                    temp_end = end + 1;
                }


                put_range(sv, start, temp_end - 1, FALSE);


                start = temp_end;


                continue;
            }


            if (isALPHANUMERIC_A(start)) {
                UV mask = (isDIGIT_A(start))
                           ? _CC_DIGIT
                             : isUPPER_A(start)
                               ? _CC_UPPER
                               : _CC_LOWER;
                UV temp_end = start + 1;


                while (temp_end <= end && _generic_isCC_A(temp_end, mask)) {
                    temp_end++;
                }
                temp_end--;


                if (temp_end - start < min_range_count) {
                    put_range(sv, start, temp_end, FALSE);
                }
                else {
                    put_code_point(sv, start);
                    sv_catpvs(sv, "-");
                    put_code_point(sv, temp_end);
                }
                start = temp_end + 1;
                continue;
            }


            if (isPUNCT_A(start) || isSPACE_A(start)) {
                while (start <= end && (isPUNCT_A(start)
                                        || isSPACE_A(start)))
                {
                    put_code_point(sv, start);
                    start++;
                }
                continue;
            }
        }


        if (   start <= end
            && (isMNEMONIC_CNTRL(start) || isMNEMONIC_CNTRL(end)))
        {
            while (isMNEMONIC_CNTRL(start) && start <= end) {
                put_code_point(sv, start);
                start++;
            }


            if (start <= end) {


                UV temp_end = end;
                while (isMNEMONIC_CNTRL(temp_end)) {
                    temp_end--;
                }


                put_range(sv, start, temp_end, FALSE);


                start = temp_end + 1;
                while (start <= end) {
                    put_code_point(sv, start);
                    start++;
                }
                break;
            }
        }


        this_end = (end < NUM_ANYOF_CODE_POINTS)
                    ? end
                    : NUM_ANYOF_CODE_POINTS - 1;
#if NUM_ANYOF_CODE_POINTS > 256
        format = (this_end < 256)
                 ? "\\x%02" UVXf "-\\x%02" UVXf
                 : "\\x{%04" UVXf "}-\\x{%04" UVXf "}";
#else
        format = "\\x%02" UVXf "-\\x%02" UVXf;
#endif
        GCC_DIAG_IGNORE_STMT(-Wformat-nonliteral);
        Perl_sv_catpvf(aTHX_ sv, format, start, this_end);
        GCC_DIAG_RESTORE_STMT;
        break;
    }
}
