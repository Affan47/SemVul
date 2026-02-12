static bool bfq_allow_bio_merge(struct request_queue *q, struct request *rq,
				struct bio *bio)
{
	struct bfq_data *bfqd = q->elevator->elevator_data;
	bool is_sync = op_is_sync(bio->bi_opf);
	struct bfq_queue *bfqq = bfqd->bio_bfqq, *new_bfqq;


	if (is_sync && !rq_is_sync(rq))
		return false;


	if (!bfqq)
		return false;


	new_bfqq = bfq_setup_cooperator(bfqd, bfqq, bio, false);
	if (new_bfqq) {


		bfq_merge_bfqqs(bfqd, bfqd->bio_bic, bfqq,
				new_bfqq);


		bfqq = new_bfqq;


		bfqd->bio_bfqq = bfqq;
	}

	return bfqq == RQ_BFQQ(rq);
}
