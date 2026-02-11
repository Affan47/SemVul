rspq_next(struct sge_rspq *q)
{
	q->cur_desc = (void *)q->cur_desc + q->iqe_len;
	if (unlikely(++q->cidx == q->size)) {
		q->cidx = 0;
		q->gen ^= 1;
		q->cur_desc = q->desc;
	}
}
