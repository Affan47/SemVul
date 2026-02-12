int bcf_hdr_parse(bcf_hdr_t *hdr, char *htxt)
{
    int len, done = 0;
    char *p = htxt;


    bcf_hrec_t *hrec = bcf_hdr_parse_line(hdr,p,&len);
    if ( !hrec || !hrec->key || strcasecmp(hrec->key,"fileformat") )
        hts_log_warning("The first line should be ##fileformat; is the VCF/BCF header broken?");
    if (bcf_hdr_add_hrec(hdr, hrec) < 0) {
        bcf_hrec_destroy(hrec);
        return -1;
    }


    hrec = bcf_hdr_parse_line(hdr,"##FILTER=<ID=PASS,Description=\"All filters passed\">",&len);
    if (bcf_hdr_add_hrec(hdr, hrec) < 0) {
        bcf_hrec_destroy(hrec);
        return -1;
    }


    do {
        while (NULL != (hrec = bcf_hdr_parse_line(hdr, p, &len))) {
            if (bcf_hdr_add_hrec(hdr, hrec) < 0) {
                bcf_hrec_destroy(hrec);
                return -1;
            }
            p += len;
        }


        if ( strncmp("#CHROM\tPOS",p,10) != 0 ) {
            char *eol = strchr(p, '\n');
            if (*p != '\0') {
                hts_log_warning("Could not parse header line: %.*s",
                    eol ? (int)(eol - p) : INT_MAX, p);
            }
            if (eol) {
                p = eol + 1;
            } else {
                done = -1;
            }
        } else {
            done = 1;
        }
    } while (!done);

    if (done < 0) {

        hts_log_error("Could not parse the header, sample line not found");
        return -1;
    }

    if (bcf_hdr_parse_sample_line(hdr,p) < 0)
        return -1;
    if (bcf_hdr_sync(hdr) < 0)
        return -1;
    bcf_hdr_check_sanity(hdr);
    return 0;
}
