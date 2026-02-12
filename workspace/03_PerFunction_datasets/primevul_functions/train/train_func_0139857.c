static int bnx2x_schedule_sp_task(struct bnx2x *bp)
{


	atomic_set(&bp->interrupt_occurred, 1);


	smp_wmb();


	return queue_delayed_work(bnx2x_wq, &bp->sp_task, 0);
}
