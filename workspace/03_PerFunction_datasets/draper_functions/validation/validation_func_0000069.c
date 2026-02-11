_unpack_spank_env_responce_msg(spank_env_responce_msg_t ** msg_ptr,
					  Buf buffer, uint16_t protocol_version)
{
	spank_env_responce_msg_t *msg;

	xassert(msg_ptr != NULL);
	msg = xmalloc(sizeof(spank_env_responce_msg_t));
	*msg_ptr = msg;

	safe_unpackstr_array(&msg->spank_job_env, &msg->spank_job_env_size,
			     buffer);
	return SLURM_SUCCESS;

unpack_error:
	slurm_free_spank_env_responce_msg(msg);
	*msg_ptr = NULL;
	return SLURM_ERROR;
}
