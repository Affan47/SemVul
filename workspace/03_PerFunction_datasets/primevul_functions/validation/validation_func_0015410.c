int bcf_hdr_add_hrec(bcf_hdr_t *hdr, bcf_hrec_t *hrec)
{
    int res;
    if ( !hrec ) return 0;

    hrec->type = BCF_HL_GEN;
    res = bcf_hdr_register_hrec(hdr,hrec);
    if (res < 0) return -1;
    if ( !res )
    {

        if ( hrec->type != BCF_HL_GEN )
        {
            bcf_hrec_destroy(hrec);
            return 0;
        }


        int i;
        for (i=0; i<hdr->nhrec; i++)
        {
            if ( hdr->hrec[i]->type!=BCF_HL_GEN ) continue;
            if ( !strcmp(hdr->hrec[i]->key,hrec->key) && !strcmp(hrec->key,"fileformat") ) break;
            if ( !strcmp(hdr->hrec[i]->key,hrec->key) && !strcmp(hdr->hrec[i]->value,hrec->value) ) break;
        }
        if ( i<hdr->nhrec )
        {
            bcf_hrec_destroy(hrec);
            return 0;
        }
    }


    int n = hdr->nhrec + 1;
    bcf_hrec_t **new_hrec = realloc(hdr->hrec, n*sizeof(bcf_hrec_t*));
    if (!new_hrec) return -1;
    hdr->hrec = new_hrec;
    hdr->hrec[hdr->nhrec] = hrec;
    hdr->dirty = 1;
    hdr->nhrec = n;

    return hrec->type==BCF_HL_GEN ? 0 : 1;
}
