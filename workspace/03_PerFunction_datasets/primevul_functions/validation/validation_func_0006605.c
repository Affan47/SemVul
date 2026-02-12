static void notify_fsp(files_struct *fsp, struct timespec when,
		       uint32_t action, const char *name)
{
	struct notify_change_event *change, *changes;
	char *tmp;

	if (fsp->notify == NULL) {


		return;
	}


	if ((fsp->notify->num_changes > 1000) || (name == NULL)) {


		TALLOC_FREE(fsp->notify->changes);
		fsp->notify->num_changes = -1;
		if (fsp->notify->requests != NULL) {
			change_notify_reply(fsp->notify->requests->req,
					    NT_STATUS_OK,
					    fsp->notify->requests->max_param,
					    fsp->notify,
					    fsp->notify->requests->reply_fn);
			change_notify_remove_request(fsp->conn->sconn,
						     fsp->notify->requests);
		}
		return;
	}


	if (fsp->notify->num_changes == -1) {
		return;
	}

	if (!(changes = talloc_realloc(
		      fsp->notify, fsp->notify->changes,
		      struct notify_change_event,
		      fsp->notify->num_changes+1))) {
		DEBUG(0, ("talloc_realloc failed\n"));
		return;
	}

	fsp->notify->changes = changes;

	change = &(fsp->notify->changes[fsp->notify->num_changes]);

	if (!(tmp = talloc_strdup(changes, name))) {
		DEBUG(0, ("talloc_strdup failed\n"));
		return;
	}

	string_replace(tmp, '/', '\\');
	change->name = tmp;

	change->when = when;
	change->action = action;
	fsp->notify->num_changes += 1;

	if (fsp->notify->requests == NULL) {


		return;
	}

	if (action == NOTIFY_ACTION_OLD_NAME) {


		return;
	}


	change_notify_reply(fsp->notify->requests->req,
			    NT_STATUS_OK,
			    fsp->notify->requests->max_param,
			    fsp->notify,
			    fsp->notify->requests->reply_fn);

	change_notify_remove_request(fsp->conn->sconn, fsp->notify->requests);
}
