static struct tevent_req *vfswrap_copy_chunk_send(struct vfs_handle_struct *handle,
						  TALLOC_CTX *mem_ctx,
						  struct tevent_context *ev,
						  struct files_struct *src_fsp,
						  off_t src_off,
						  struct files_struct *dest_fsp,
						  off_t dest_off,
						  off_t num)
{
	struct tevent_req *req;
	struct vfs_cc_state *vfs_cc_state;
	NTSTATUS status;

	DEBUG(10, ("performing server side copy chunk of length %lu\n",
		   (unsigned long)num));

	req = tevent_req_create(mem_ctx, &vfs_cc_state, struct vfs_cc_state);
	if (req == NULL) {
		return NULL;
	}

	status = vfs_stat_fsp(src_fsp);
	if (tevent_req_nterror(req, status)) {
		return tevent_req_post(req, ev);
	}

	if (src_fsp->fsp_name->st.st_ex_size < src_off + num) {


		tevent_req_nterror(req, NT_STATUS_INVALID_VIEW_SIZE);
		return tevent_req_post(req, ev);
	}


	while (vfs_cc_state->copied < num) {
		ssize_t ret;
		struct lock_struct lck;
		int saved_errno;

		off_t this_num = MIN(sizeof(vfs_cc_state->buf),
				     num - vfs_cc_state->copied);

		init_strict_lock_struct(src_fsp,
					src_fsp->op->global->open_persistent_id,
					src_off,
					this_num,
					READ_LOCK,
					&lck);

		if (!SMB_VFS_STRICT_LOCK(src_fsp->conn, src_fsp, &lck)) {
			tevent_req_nterror(req, NT_STATUS_FILE_LOCK_CONFLICT);
			return tevent_req_post(req, ev);
		}

		ret = SMB_VFS_PREAD(src_fsp, vfs_cc_state->buf,
				    this_num, src_off);
		if (ret == -1) {
			saved_errno = errno;
		}

		SMB_VFS_STRICT_UNLOCK(src_fsp->conn, src_fsp, &lck);

		if (ret == -1) {
			errno = saved_errno;
			tevent_req_nterror(req, map_nt_error_from_unix(errno));
			return tevent_req_post(req, ev);
		}
		if (ret != this_num) {

			tevent_req_nterror(req, NT_STATUS_IO_DEVICE_ERROR);
			return tevent_req_post(req, ev);
		}

		src_off += ret;

		init_strict_lock_struct(dest_fsp,
					dest_fsp->op->global->open_persistent_id,
					dest_off,
					this_num,
					WRITE_LOCK,
					&lck);

		if (!SMB_VFS_STRICT_LOCK(dest_fsp->conn, dest_fsp, &lck)) {
			tevent_req_nterror(req, NT_STATUS_FILE_LOCK_CONFLICT);
			return tevent_req_post(req, ev);
		}

		ret = SMB_VFS_PWRITE(dest_fsp, vfs_cc_state->buf,
				     this_num, dest_off);
		if (ret == -1) {
			saved_errno = errno;
		}

		SMB_VFS_STRICT_UNLOCK(src_fsp->conn, src_fsp, &lck);

		if (ret == -1) {
			errno = saved_errno;
			tevent_req_nterror(req, map_nt_error_from_unix(errno));
			return tevent_req_post(req, ev);
		}
		if (ret != this_num) {

			tevent_req_nterror(req, NT_STATUS_IO_DEVICE_ERROR);
			return tevent_req_post(req, ev);
		}
		dest_off += ret;

		vfs_cc_state->copied += this_num;
	}

	tevent_req_done(req);
	return tevent_req_post(req, ev);
}
