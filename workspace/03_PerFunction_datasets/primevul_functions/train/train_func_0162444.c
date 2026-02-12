finish_bgprint(fz_context *ctx)
{
	int status;

	if (!bgprint.active)
		return;


	status = wait_for_bgprint_to_finish();
	if (status == RENDER_OK)
	{

		return;
	}

	if (status == RENDER_FATAL)
	{

		fz_throw(ctx, FZ_ERROR_GENERIC, "Failed to render page");
	}
	bgprint.started = 1;
	bgprint.solo = 1;
	mu_trigger_semaphore(&bgprint.start);
	status = wait_for_bgprint_to_finish();
	if (status != 0)
	{

		fz_throw(ctx, FZ_ERROR_GENERIC, "Failed to render page");
	}
}
