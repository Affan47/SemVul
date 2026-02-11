on_temperature_changed ()
{
	if (color_by == &P_PHASE)
		throttle_update_temperature.queue
			(sigc::mem_fun (*this, &TableTable::update_colors), true);
}
