static bool smbd_dirptr_lanman2_match_fn(TALLOC_CTX *ctx,
					 void *private_data,
					 const char *dname,
					 const char *mask,
					 char **_fname)
{
	struct smbd_dirptr_lanman2_state *state =
		(struct smbd_dirptr_lanman2_state *)private_data;
	bool ok;
	char mangled_name[13];
	bool got_match;
	const char *fname;


	if (mangle_must_mangle(dname, state->conn->params)) {


		NTSTATUS status;
		size_t ret_len = 0;
		size_t len = (strlen(dname) + 2) * 4;
		uint8_t *tmp = talloc_array(talloc_tos(),
					uint8_t,
					len);

		status = srvstr_push(NULL,
			FLAGS2_UNICODE_STRINGS,
			tmp,
			dname,
			len,
			STR_TERMINATE,
			&ret_len);

		TALLOC_FREE(tmp);

		if (!NT_STATUS_IS_OK(status)) {
			return false;
		}

		ok = name_to_8_3(dname, mangled_name,
				 true, state->conn->params);
		if (!ok) {
			return false;
		}
		fname = mangled_name;
	} else {
		fname = dname;
	}

	got_match = exact_match(state->has_wild,
				state->conn->case_sensitive,
				fname, mask);
	state->got_exact_match = got_match;
	if (!got_match) {
		got_match = mask_match(fname, mask,
				       state->conn->case_sensitive);
	}

	if(!got_match && state->check_mangled_names &&
	   !mangle_is_8_3(fname, false, state->conn->params)) {


		ok = name_to_8_3(fname, mangled_name,
				 false, state->conn->params);
		if (!ok) {
			return false;
		}

		got_match = exact_match(state->has_wild,
					state->conn->case_sensitive,
					mangled_name, mask);
		state->got_exact_match = got_match;
		if (!got_match) {
			got_match = mask_match(mangled_name, mask,
					       state->conn->case_sensitive);
		}
	}

	if (!got_match) {
		return false;
	}

	*_fname = talloc_strdup(ctx, fname);
	if (*_fname == NULL) {
		return false;
	}

	return true;
}
