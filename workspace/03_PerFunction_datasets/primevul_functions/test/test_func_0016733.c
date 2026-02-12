static NTSTATUS open_mode_check(connection_struct *conn,
				struct share_mode_lock *lck,
				uint32 access_mask,
				uint32 share_access)
{
	int i;

	if(lck->data->num_share_modes == 0) {
		return NT_STATUS_OK;
	}

	if (is_stat_open(access_mask)) {


		return NT_STATUS_OK;
	}


#if defined(DEVELOPER)
	for(i = 0; i < lck->data->num_share_modes; i++) {
		validate_my_share_entries(conn->sconn, i,
					  &lck->data->share_modes[i]);
	}
#endif


	for(i = 0; i < lck->data->num_share_modes; i++) {

		if (!is_valid_share_mode_entry(&lck->data->share_modes[i])) {
			continue;
		}


		if (share_conflict(&lck->data->share_modes[i],
				   access_mask, share_access)) {

			if (share_mode_stale_pid(lck->data, i)) {
				continue;
			}

			return NT_STATUS_SHARING_VIOLATION;
		}
	}

	return NT_STATUS_OK;
}
