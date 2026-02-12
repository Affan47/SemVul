static inline void set_kthread_struct(void *kthread)
{


	current->set_child_tid = (__force void __user *)kthread;
}
