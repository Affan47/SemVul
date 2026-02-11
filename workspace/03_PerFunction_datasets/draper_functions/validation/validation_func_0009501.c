acct_gather_energy_p_get_data(enum acct_energy_type data_type,
					 void *data)
{
	int rc = SLURM_SUCCESS;
	acct_gather_energy_t *energy = (acct_gather_energy_t *)data;
	time_t *last_poll = (time_t *)data;

	xassert(_run_in_daemon());

	switch (data_type) {
	case ENERGY_DATA_JOULES_TASK:
		if (local_energy->current_watts == NO_VAL)
			energy->consumed_energy = NO_VAL;
		else
			_get_joules_task(energy);
		break;
	case ENERGY_DATA_STRUCT:
		memcpy(energy, local_energy, sizeof(acct_gather_energy_t));
		break;
	case ENERGY_DATA_LAST_POLL:
		*last_poll = local_energy->poll_time;
		break;
	default:
		error("acct_gather_energy_p_get_data: unknown enum %d",
		      data_type);
		rc = SLURM_ERROR;
		break;
	}
	return rc;
}
