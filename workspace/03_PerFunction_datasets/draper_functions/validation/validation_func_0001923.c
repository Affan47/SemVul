serve_battery_data(GkrellmdMonitor *mon, gboolean first_serve)
	{
	Battery		*bat;
	GList		*list;
	gchar		buf[128];

	gkrellmd_set_serve_name(mon, "battery");
	for (list = battery_list; list; list = list->next)
		{
		bat = (Battery *) list->data;

		if (   (!bat->changed && !first_serve)
			|| (   !gkrellmd_check_client_version(mon, 2,1,9)
				&& bat->id > 0
			   )
		   )
			continue;
		snprintf(buf, sizeof(buf), "%d %d %d %d %d %d\n",
					bat->present, bat->on_line, bat->charging,
					bat->percent, bat->time_left, bat->id);
		gkrellmd_serve_data(mon, buf);
		}
	}
