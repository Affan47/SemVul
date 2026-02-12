static void kill_procs(struct list_head *to_kill, int forcekill, int trapno,
			  int fail, struct page *page, unsigned long pfn,
			  int flags)
{
	struct to_kill *tk, *next;

	list_for_each_entry_safe (tk, next, to_kill, nd) {
		if (forcekill) {


			if (fail || tk->addr_valid == 0) {
				pr_err("Memory failure: %#lx: forcibly killing %s:%d because of failure to unmap corrupted page\n",
				       pfn, tk->tsk->comm, tk->tsk->pid);
				force_sig(SIGKILL, tk->tsk);
			}


			else if (kill_proc(tk->tsk, tk->addr, trapno,
					      pfn, page, flags) < 0)
				pr_err("Memory failure: %#lx: Cannot send advisory machine check signal to %s:%d\n",
				       pfn, tk->tsk->comm, tk->tsk->pid);
		}
		put_task_struct(tk->tsk);
		kfree(tk);
	}
}
