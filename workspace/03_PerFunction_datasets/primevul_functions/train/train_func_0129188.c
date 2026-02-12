void free_kthread_struct(struct task_struct *k)
{


	kfree(to_kthread(k));
}
