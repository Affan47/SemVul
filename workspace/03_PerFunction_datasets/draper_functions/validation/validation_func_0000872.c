bam_plp_reset(bam_plp_t iter)
{
	lbnode_t *p, *q;
	iter->max_tid = iter->max_pos = -1;
	iter->tid = iter->pos = 0;
	iter->is_eof = 0;
	for (p = iter->head; p->next;) {
		q = p->next;
		mp_free(iter->mp, p);
		p = q;
	}
	iter->head = iter->tail;
}
