gsb_form_scheduler_get_limit_date ( void )
{
    GtkWidget *entry;
    GDate *date;

    entry = gsb_form_scheduler_get_element_widget(SCHEDULED_FORM_LIMIT_DATE);

    if (!entry
	||
	gsb_form_widget_check_empty (entry)
	||
	!GTK_WIDGET_VISIBLE (entry))
	return NULL;

    date = gsb_calendar_entry_get_date (entry);
    return date;
}
