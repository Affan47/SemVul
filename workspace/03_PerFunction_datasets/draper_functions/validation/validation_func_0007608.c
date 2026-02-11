brasero_job_get_input_type (BraseroJob *self, BraseroTrackType *type)
{
	BraseroBurnResult result = BRASERO_BURN_OK;
	BraseroJobPrivate *priv;

	BRASERO_JOB_DEBUG (self);

	priv = BRASERO_JOB_PRIVATE (self);
	if (!priv->previous) {
		BraseroBurnSession *session;

		session = brasero_task_ctx_get_session (priv->ctx);
		result = brasero_burn_session_get_input_type (session, type);
	}
	else {
		BraseroJobPrivate *prev_priv;

		prev_priv = BRASERO_JOB_PRIVATE (priv->previous);
		memcpy (type, &prev_priv->type, sizeof (BraseroTrackType));
		result = BRASERO_BURN_OK;
	}

	return result;
}
