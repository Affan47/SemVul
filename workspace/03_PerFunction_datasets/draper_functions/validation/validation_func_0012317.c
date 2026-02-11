ea_calendar_item_get_n_children (AtkObject *accessible)
{
	AtkGObjectAccessible *atk_gobj;
	GObject *g_obj;
	ECalendarItem *calitem;
	gint n_children = 0;
	gint start_year, start_month, start_day;
	gint end_year, end_month, end_day;
	GDate *start_date, *end_date;

	g_return_val_if_fail (EA_IS_CALENDAR_ITEM (accessible), -1);

	atk_gobj = ATK_GOBJECT_ACCESSIBLE (accessible);
	g_obj = atk_gobject_accessible_get_object (atk_gobj);
	if (!g_obj)
		return -1;

	calitem = E_CALENDAR_ITEM (g_obj);
	if (!e_calendar_item_get_date_range (calitem, &start_year,
					     &start_month, &start_day,
					     &end_year, &end_month,
					     &end_day))
		return 0;

	start_date = g_date_new_dmy (start_day, start_month + 1, start_year);
	end_date = g_date_new_dmy (end_day, end_month + 1, end_year);

	n_children = g_date_days_between (start_date, end_date) + 1;
	g_free (start_date);
	g_free (end_date);
	return n_children;
}
