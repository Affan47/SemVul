create_alert_objects(GkrellmAlert *alert)
	{
	GkrellmAlertdecal		*ad;


	if (alert->cb_trigger)
		(*alert->cb_trigger)(alert, alert->cb_trigger_data);
	if (!alert->panel)
		return FALSE;
	ad = &alert->ad;
	if (!alert->ad.pixmap )
		{
		ad->x = 0;
		ad->y = 0;
		ad->w = alert->panel->w;
		ad->h = alert->panel->h;
		gkrellm_render_default_alert_decal(alert);
		}


	ad->decal = gkrellm_create_decal_pixmap(NULL, ad->pixmap, ad->mask,
				ad->nframes, NULL, ad->x, ad->y);
	gkrellm_insert_decal(alert->panel, ad->decal, FALSE );

#if 0
	k = gkrellm_create_krell(NULL,
			gkrellm_krell_mini_piximage(), gkrellm_krell_mini_style());
	k->y0 = 5;
	k->full_scale = 100;

	alert->ak.krell = k;
	gkrellm_insert_krell(alert->panel, k, TRUE);
#endif
	return TRUE;
	}
