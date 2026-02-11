blk_should_fake_timeout(struct request_queue *q)
{
	if (!test_bit(QUEUE_FLAG_FAIL_IO, &q->queue_flags))
		return 0;

	return should_fail(&fail_io_timeout, 1);
}
