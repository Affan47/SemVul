__releases(journal->j_state_lock)
{
	DEFINE_WAIT(wait);

	if (WARN_ON(!journal->j_running_transaction ||
		    journal->j_running_transaction->t_state != T_SWITCH)) {
		read_unlock(&journal->j_state_lock);
		return;
	}
	prepare_to_wait(&journal->j_wait_transaction_locked, &wait,
			TASK_UNINTERRUPTIBLE);
	read_unlock(&journal->j_state_lock);


	schedule();
	finish_wait(&journal->j_wait_transaction_locked, &wait);
}
