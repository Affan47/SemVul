static int vbg_hgcm_do_call(struct vbg_dev *gdev, struct vmmdev_hgcm_call *call,
			    u32 timeout_ms, bool *leak_it)
{
	int rc, cancel_rc, ret;
	long timeout;

	*leak_it = false;

	rc = vbg_req_perform(gdev, call);


	if (rc < 0) {
		call->header.result = rc;
		return 0;
	}

	if (rc != VINF_HGCM_ASYNC_EXECUTE)
		return 0;


	if (timeout_ms == U32_MAX)
		timeout = MAX_SCHEDULE_TIMEOUT;
	else
		timeout = msecs_to_jiffies(timeout_ms);

	timeout = wait_event_interruptible_timeout(
					gdev->hgcm_wq,
					hgcm_req_done(gdev, &call->header),
					timeout);


	if (timeout > 0)
		return 0;

	if (timeout == 0)
		ret = -ETIMEDOUT;
	else
		ret = -EINTR;


	cancel_rc = hgcm_cancel_call(gdev, call);
	if (cancel_rc >= 0)
		return ret;


	if (cancel_rc == VERR_NOT_FOUND || cancel_rc == VERR_SEM_DESTROYED)
		timeout = msecs_to_jiffies(500);
	else
		timeout = msecs_to_jiffies(2000);

	timeout = wait_event_timeout(gdev->hgcm_wq,
				     hgcm_req_done(gdev, &call->header),
				     timeout);

	if (WARN_ON(timeout == 0)) {

		vbg_err("%s: Call timedout and cancellation failed, leaking the request\n",
			__func__);
		*leak_it = true;
		return ret;
	}


	return 0;
}
