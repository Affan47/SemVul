*/
static void bfq_prepare_request(struct request *rq, struct bio *bio)
{


	rq->elv.priv[0] = rq->elv.priv[1] = NULL;
}
