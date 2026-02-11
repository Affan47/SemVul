e_date_edit_set_time (EDateEdit *dedit,
                      time_t the_time)
{
	EDateEditPrivate *priv;
	struct tm tmp_tm;
	gboolean date_changed = FALSE, time_changed = FALSE;

	g_return_if_fail (E_IS_DATE_EDIT (dedit));

	priv = dedit->priv;

	if (the_time == -1) {
		date_changed = e_date_edit_set_date_internal (
			dedit, TRUE,
			TRUE, 0, 0, 0);
		time_changed = e_date_edit_set_time_internal (
			dedit, TRUE,
			TRUE, 0, 0);
	} else {
		if (the_time == 0) {
			if (priv->time_callback) {
				tmp_tm = (*priv->time_callback) (dedit, priv->time_callback_data);
			} else {
				the_time = time (NULL);
				tmp_tm = *localtime (&the_time);
			}
		} else {
			tmp_tm = *localtime (&the_time);
		}

		date_changed = e_date_edit_set_date_internal (
			dedit, TRUE,
			FALSE,
			tmp_tm.tm_year,
			tmp_tm.tm_mon,
			tmp_tm.tm_mday);
		time_changed = e_date_edit_set_time_internal (
			dedit, TRUE,
			FALSE,
			tmp_tm.tm_hour,
			tmp_tm.tm_min);
	}

	e_date_edit_update_date_entry (dedit);
	e_date_edit_update_time_entry (dedit);
	e_date_edit_update_time_combo_state (dedit);


	if (date_changed || time_changed)
		g_signal_emit (dedit, signals[CHANGED], 0);
}
