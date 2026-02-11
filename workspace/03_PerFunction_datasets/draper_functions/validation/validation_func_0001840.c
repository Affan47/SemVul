destroy_forward_struct(forward_struct_t *forward_struct)
{
	if (forward_struct) {
		xfree(forward_struct->buf);
		xfree(forward_struct->forward_msg);
		slurm_mutex_destroy(&forward_struct->forward_mutex);
		pthread_cond_destroy(&forward_struct->notify);
		xfree(forward_struct);
	}
}
