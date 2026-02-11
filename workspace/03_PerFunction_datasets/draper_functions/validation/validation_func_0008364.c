git_push_status_foreach(git_push *push,
		int (*cb)(const char *ref, const char *msg, void *data),
		void *data)
{
	push_status *status;
	unsigned int i;

	git_vector_foreach(&push->status, i, status) {
		int error = cb(status->ref, status->msg, data);
		if (error)
			return giterr_set_after_callback(error);
	}

	return 0;
}
