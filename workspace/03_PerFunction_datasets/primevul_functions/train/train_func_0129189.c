void kthread_unpark(struct task_struct *k)
{
	struct kthread *kthread = to_kthread(k);

	clear_bit(KTHREAD_SHOULD_PARK, &kthread->flags);


	if (test_and_clear_bit(KTHREAD_IS_PARKED, &kthread->flags)) {


		if (test_bit(KTHREAD_IS_PER_CPU, &kthread->flags))
			__kthread_bind(k, kthread->cpu, TASK_PARKED);
		wake_up_state(k, TASK_PARKED);
	}
}
