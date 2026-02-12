static void set_work_pool_and_clear_pending(struct work_struct *work,
					    int pool_id)
{


	smp_wmb();
	set_work_data(work, (unsigned long)pool_id << WORK_OFFQ_POOL_SHIFT, 0);


	smp_mb();
}
