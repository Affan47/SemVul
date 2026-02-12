__must_hold(&journal->j_state_lock)
{
	transaction_t *t = journal->j_running_transaction;
	int needed;
	int total = blocks + rsv_blocks;


	if (t->t_state != T_RUNNING) {
		WARN_ON_ONCE(t->t_state >= T_FLUSH);
		wait_transaction_locked(journal);
		__acquire(&journal->j_state_lock);
		return 1;
	}


	needed = atomic_add_return(total, &t->t_outstanding_credits);
	if (needed > journal->j_max_transaction_buffers) {


		atomic_sub(total, &t->t_outstanding_credits);


		if (atomic_read(&journal->j_reserved_credits) + total >
		    journal->j_max_transaction_buffers) {
			read_unlock(&journal->j_state_lock);
			jbd2_might_wait_for_commit(journal);
			wait_event(journal->j_wait_reserved,
				   atomic_read(&journal->j_reserved_credits) + total <=
				   journal->j_max_transaction_buffers);
			__acquire(&journal->j_state_lock);
			return 1;
		}

		wait_transaction_locked(journal);
		__acquire(&journal->j_state_lock);
		return 1;
	}


	if (jbd2_log_space_left(journal) < journal->j_max_transaction_buffers) {
		atomic_sub(total, &t->t_outstanding_credits);
		read_unlock(&journal->j_state_lock);
		jbd2_might_wait_for_commit(journal);
		write_lock(&journal->j_state_lock);
		if (jbd2_log_space_left(journal) <
					journal->j_max_transaction_buffers)
			__jbd2_log_wait_for_space(journal);
		write_unlock(&journal->j_state_lock);
		__acquire(&journal->j_state_lock);
		return 1;
	}


	if (!rsv_blocks)
		return 0;

	needed = atomic_add_return(rsv_blocks, &journal->j_reserved_credits);

	if (needed > journal->j_max_transaction_buffers / 2) {
		sub_reserved_credits(journal, rsv_blocks);
		atomic_sub(total, &t->t_outstanding_credits);
		read_unlock(&journal->j_state_lock);
		jbd2_might_wait_for_commit(journal);
		wait_event(journal->j_wait_reserved,
			 atomic_read(&journal->j_reserved_credits) + rsv_blocks
			 <= journal->j_max_transaction_buffers / 2);
		__acquire(&journal->j_state_lock);
		return 1;
	}
	return 0;
}
