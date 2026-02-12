bcf_hrec_t *bcf_hdr_parse_line(const bcf_hdr_t *h, const char *line, int *len)
{
    const char *p = line;
    if (p[0] != '#' || p[1] != '#') { *len = 0; return NULL; }
    p += 2;

    const char *q = p;
    while ( *q && *q!='=' && *q != '\n' ) q++;
    ptrdiff_t n = q-p;
    if ( *q!='=' || !n ) { *len = q-line+1; return NULL; }

    bcf_hrec_t *hrec = (bcf_hrec_t*) calloc(1,sizeof(bcf_hrec_t));
    if (!hrec) return NULL;
    hrec->key = (char*) malloc(sizeof(char)*(n+1));
    if (!hrec->key) goto fail;
    memcpy(hrec->key,p,n);
    hrec->key[n] = 0;

    p = ++q;
    if ( *p!='<' )
    {
        while ( *q && *q!='\n' ) q++;
        hrec->value = (char*) malloc((q-p+1)*sizeof(char));
        if (!hrec->value) goto fail;
        memcpy(hrec->value, p, q-p);
        hrec->value[q-p] = 0;
        *len = q - line + (*q ? 1 : 0);
        return hrec;
    }


    int nopen = 1;
    while ( *q && *q!='\n' && nopen>0 )
    {
        p = ++q;
        while ( *q && *q==' ' ) { p++; q++; }

        if (p==q && *q && (isalpha_c(*q) || *q=='_'))
        {
            q++;
            while ( *q && (isalnum_c(*q) || *q=='_' || *q=='.') ) q++;
        }
        n = q-p;
        int m = 0;
        while ( *q && *q==' ' ) { q++; m++; }
        if ( *q!='=' || !n )
        {

            while ( *q && *q!='\n' ) q++;
            hts_log_error("Could not parse the header line: \"%.*s\"",
                (int) (q - line), line);
            *len = q - line + (*q ? 1 : 0);
            bcf_hrec_destroy(hrec);
            return NULL;
        }
        if (bcf_hrec_add_key(hrec, p, q-p-m) < 0) goto fail;
        p = ++q;
        while ( *q && *q==' ' ) { p++; q++; }
        int quoted = *p=='"' ? 1 : 0;
        if ( quoted ) p++, q++;
        while ( *q && *q != '\n' )
        {
            if ( quoted ) { if ( *q=='"' && !is_escaped(p,q) ) break; }
            else
            {
                if ( *q=='<' ) nopen++;
                if ( *q=='>' ) nopen--;
                if ( !nopen ) break;
                if ( *q==',' && nopen==1 ) break;
            }
            q++;
        }
        const char *r = q;
        while ( r > p && r[-1] == ' ' ) r--;
        if (bcf_hrec_set_val(hrec, hrec->nkeys-1, p, r-p, quoted) < 0)
            goto fail;
        if ( quoted && *q=='"' ) q++;
        if ( *q=='>' ) { nopen--; q++; }
    }


    int nonspace = 0;
    p = q;
    while ( *q && *q!='\n' ) { nonspace |= !isspace_c(*q); q++; }
    if (nonspace) {
        hts_log_warning("Dropped trailing junk from header line '%.*s'", (int) (q - line), line);
    }

    *len = q - line + (*q ? 1 : 0);
    return hrec;

 fail:
    bcf_hrec_destroy(hrec);
    return NULL;
}
