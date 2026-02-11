brasero_job_set_progress (BraseroJob *self,
			  gdouble progress)
{
	BraseroJobPrivate *priv;


	priv = BRASERO_JOB_PRIVATE (self);
	if (priv->next)
		return BRASERO_BURN_ERR;

	if (progress < 0.0 || progress > 1.0) {
		BRASERO_JOB_LOG (self, "Tried to set an insane progress value (%lf)", progress);
		return BRASERO_BURN_ERR;
	}

	return brasero_task_ctx_set_progress (priv->ctx, progress);
}
