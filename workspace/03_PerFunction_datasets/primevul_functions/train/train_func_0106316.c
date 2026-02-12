static void diffcore_skip_stat_unmatch(struct diff_options *diffopt)
{
	int i;
	struct diff_queue_struct *q = &diff_queued_diff;
	struct diff_queue_struct outq;
	outq.queue = NULL;
	outq.nr = outq.alloc = 0;

	for (i = 0; i < q->nr; i++) {
		struct diff_filepair *p = q->queue[i];


		if (!DIFF_FILE_VALID(p->one) ||
		    !DIFF_FILE_VALID(p->two) ||
		    (p->one->sha1_valid && p->two->sha1_valid) ||
		    (p->one->mode != p->two->mode) ||
		    diff_populate_filespec(p->one, 1) ||
		    diff_populate_filespec(p->two, 1) ||
		    (p->one->size != p->two->size) ||
		    !diff_filespec_is_identical(p->one, p->two))
			diff_q(&outq, p);
		else {


			if (!DIFF_OPT_TST(diffopt, NO_INDEX))
				diffopt->skip_stat_unmatch++;
			diff_free_filepair(p);
		}
	}
	free(q->queue);
	*q = outq;
}
