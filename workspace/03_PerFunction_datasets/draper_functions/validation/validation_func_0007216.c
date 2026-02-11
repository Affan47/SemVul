_unpack_step_complete_msg(step_complete_msg_t ** msg_ptr, Buf buffer,
			  uint16_t protocol_version)
{
	step_complete_msg_t *msg;

	msg = xmalloc(sizeof(step_complete_msg_t));
	*msg_ptr = msg;

	safe_unpack32(&msg->job_id, buffer);
	safe_unpack32(&msg->job_step_id, buffer);
	safe_unpack32(&msg->range_first, buffer);
	safe_unpack32(&msg->range_last, buffer);
	safe_unpack32(&msg->step_rc, buffer);
	if (jobacctinfo_unpack(&msg->jobacct, protocol_version,
			       PROTOCOL_TYPE_SLURM, buffer)
	    != SLURM_SUCCESS)
		goto unpack_error;

	return SLURM_SUCCESS;

unpack_error:
	slurm_free_step_complete_msg(msg);
	*msg_ptr = NULL;
	return SLURM_ERROR;
}
