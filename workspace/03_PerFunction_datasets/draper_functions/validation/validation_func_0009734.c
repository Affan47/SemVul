name_field_activate (NemoEntry *name_field, gpointer callback_data)
{
	g_assert (NEMO_IS_ENTRY (name_field));
	g_assert (NEMO_IS_PROPERTIES_WINDOW (callback_data));


	name_field_done_editing (name_field, NEMO_PROPERTIES_WINDOW (callback_data));

	nemo_entry_select_all_at_idle (name_field);
}
