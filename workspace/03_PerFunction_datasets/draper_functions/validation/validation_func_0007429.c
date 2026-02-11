read_bam(void *data, bam1_t *b)
{
	aux_t *aux = (aux_t*)data;
	int ret = bam_iter_read(aux->fp, aux->iter, b);
	if ((int)b->core.qual < aux->min_mapQ) b->core.flag |= BAM_FUNMAP;
	return ret;
}
