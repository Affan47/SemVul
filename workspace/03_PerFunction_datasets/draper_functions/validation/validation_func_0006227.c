e_date_edit_set_date_and_time_of_day (EDateEdit *dedit,
                                      gint year,
                                      gint month,
                                      gint day,
                                      gint hour,
                                      gint minute)
{
	gboolean date_changed, time_changed;

	g_return_if_fail (E_IS_DATE_EDIT (dedit));

	date_changed = e_date_edit_set_date_internal (
		dedit, TRUE, FALSE,
		year - 1900, month - 1, day);
	time_changed = e_date_edit_set_time_internal (
		dedit, TRUE, FALSE,
		hour, minute);

	e_date_edit_update_date_entry (dedit);
	e_date_edit_update_time_entry (dedit);
	e_date_edit_update_time_combo_state (dedit);

	if (date_changed || time_changed)
		g_signal_emit (dedit, signals[CHANGED], 0);
}
