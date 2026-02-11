wasp_match_regex( wasp_regex regex,
                           const char* str, const char* flagstr,
                           const char** head, const char** tail
){
    int flags = 0;
    if( flagstr ){
        for( ; *flagstr; flagstr++ )switch( *flagstr ){
        case 'b':
            flags |= REG_NOTBOL;
            break;
        case 'e':
            flags |= REG_NOTEOL;
            break;
        default:
            wasp_errf( wasp_es_rx, "s", "regex flag not recognized" );
        }
    };

    int ct = regex->rx.re_nsub + 1;
    regmatch_t* mx = alloca( sizeof( regmatch_t ) * ct );
    int rs = regexec( &( regex->rx ), str, ct, mx, flags );
    if( rs == 0 ){
        const char* b = str + mx[0].rm_so;
        const char* e = str + mx[0].rm_eo;
        if( head ) (*head) = b;
        if( tail ) (*tail) = e;
        if( ct == 1 ){
            return wasp_vf_string( wasp_string_fm( b, e - b ) );
        }
        wasp_tc tc = wasp_make_tc( );
        int ix;
        for( ix = 1; ix < ct; ix ++ ){
            if( mx[ix].rm_so == -1 ){
                wasp_tc_add( tc, wasp_vf_false( ) );
            }else{
                b = str + mx[ix].rm_so;
                e = str + mx[ix].rm_eo;
                wasp_tc_add(
                    tc, wasp_vf_string( wasp_string_fm( b, e - b ) )
                );
            }
        }
        return wasp_vf_pair( tc->head );
    }else if( rs == REG_NOMATCH ){
        return wasp_vf_false( );
    }else{
        wasp_regex_error( regex, rs );
    }
}
