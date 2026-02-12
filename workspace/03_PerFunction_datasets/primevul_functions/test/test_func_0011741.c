static inline u32 task_sid_binder(const struct task_struct *task)
{


	return task_sid_obj(task);
}
