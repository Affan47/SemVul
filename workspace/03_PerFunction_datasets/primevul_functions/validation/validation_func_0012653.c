static inline bool may_ptrace_stop(void)
{
	if (!likely(current->ptrace))
		return false;


	if (unlikely(current->mm->core_state) &&
	    unlikely(current->mm == current->parent->mm))
		return false;

	return true;
}
