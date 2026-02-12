static void clear_work_data(struct work_struct *work)
{
	smp_wmb();
	set_work_data(work, WORK_STRUCT_NO_POOL, 0);
}
