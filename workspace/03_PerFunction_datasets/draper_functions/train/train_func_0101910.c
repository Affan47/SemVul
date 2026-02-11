bam_plp_init(bam_plp_auto_f func, void *data)
{
	bam_plp_t iter;
	iter = calloc(1, sizeof(struct __bam_plp_t));
	iter->mp = mp_init();
	iter->head = iter->tail = mp_alloc(iter->mp);
	iter->dummy = mp_alloc(iter->mp);
	iter->max_tid = iter->max_pos = -1;
	iter->flag_mask = BAM_DEF_MASK;
	iter->maxcnt = 8000;
	if (func) {
		iter->func = func;
		iter->data = data;
		iter->b = bam_init1();
	}
	return iter;
}
