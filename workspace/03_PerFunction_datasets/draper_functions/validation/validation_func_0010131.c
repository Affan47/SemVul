memstick_init_req_sg(struct memstick_request *mrq, unsigned char tpc,
			  const struct scatterlist *sg)
{
	mrq->tpc = tpc;
	if (tpc & 8)
		mrq->data_dir = WRITE;
	else
		mrq->data_dir = READ;

	mrq->sg = *sg;
	mrq->long_data = 1;

	if (tpc == MS_TPC_SET_CMD || tpc == MS_TPC_EX_SET_CMD)
		mrq->need_card_int = 1;
	else
		mrq->need_card_int = 0;
}
