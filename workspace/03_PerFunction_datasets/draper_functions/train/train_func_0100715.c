_bcf1_sync_alleles(bcf_hdr_t *hdr, bcf1_t *line, int nals)
{
    line->n_allele = nals;
    hts_expand(char*, line->n_allele, line->d.m_allele, line->d.allele);

    char *als = line->d.als;
    int n = 0;
    while (n<nals)
    {
        line->d.allele[n] = als;
        while ( *als ) als++;
        als++;
        n++;
    }
    line->n_allele = nals;
    line->d.shared_dirty |= BCF1_DIRTY_ALS;
    return 0;
}
