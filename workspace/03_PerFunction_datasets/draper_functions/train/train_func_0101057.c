read_bam(void *data, bam1_t *b)
{
	aux_t *aux = (aux_t*)data;
	int ret = aux->iter? bam_iter_read(aux->fp, aux->iter, b) : bam_read1(aux->fp, b);
	if (!(b->core.flag&BAM_FUNMAP)) {
		if ((int)b->core.qual < aux->min_mapQ) b->core.flag |= BAM_FUNMAP;
		else if (aux->min_len && bam_cigar2qlen(&b->core, bam1_cigar(b)) < aux->min_len) b->core.flag |= BAM_FUNMAP;
	}
	return ret;
}
