static inline void blk_queue_enter_live(struct request_queue *q)
{


	percpu_ref_get(&q->q_usage_counter);
}
