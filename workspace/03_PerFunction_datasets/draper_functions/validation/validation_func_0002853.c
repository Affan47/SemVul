wbcg_autosave_activate (WBCGtk *wbcg)
{
	wbcg_autosave_cancel (wbcg);

	if (wbcg->autosave_time > 0) {
		int secs = MIN (wbcg->autosave_time, G_MAXINT / 1000);
		wbcg->autosave_timer =
			g_timeout_add (secs * 1000,
				       (GSourceFunc) cb_autosave,
				       wbcg);
	}
}
