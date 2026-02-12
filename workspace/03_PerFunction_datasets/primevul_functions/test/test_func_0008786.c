callbacks_benchmark_clicked (GtkButton *button, gpointer   user_data)
{

	gerbv_render_info_t renderInfo = {1.0, 1.0, 0, 0,
					GERBV_RENDER_TYPE_GDK, 640, 480};

	if (!interface_get_alert_dialog_response(_("Performance benchmark"),
			_("Application will be unresponsive for 1 minute! "
			"Run performance benchmark?"),
			FALSE, NULL, GTK_STOCK_OK, GTK_STOCK_CANCEL))
		return;

	GERB_COMPILE_WARNING(_("Running full zoom benchmark..."));
	while (g_main_context_iteration(NULL, FALSE)) {}


	gerbv_render_zoom_to_fit_display (mainProject, &renderInfo);
	callbacks_support_benchmark (&renderInfo);

	GERB_COMPILE_WARNING(_("Running x5 zoom benchmark..."));
	while (g_main_context_iteration(NULL, FALSE)) {}

	renderInfo.lowerLeftX += (screenRenderInfo.displayWidth /
				screenRenderInfo.scaleFactorX) / 3.0;
	renderInfo.lowerLeftY += (screenRenderInfo.displayHeight /
				screenRenderInfo.scaleFactorY) / 3.0;
	renderInfo.scaleFactorX *= 5;
	renderInfo.scaleFactorY *= 5;
	callbacks_support_benchmark (&renderInfo);
}
