set_controls
	(
	)
	{
	setting_controls = true;
	ExultStudio *studio = ExultStudio::get_instance();
	Combo_member *m = combo->get(selected);
	if (!m)
		{
		studio->set_spin("combo_locx", 0, false);
		studio->set_spin("combo_locy", 0, false);
		studio->set_spin("combo_locz", 0, false);
		studio->set_spin("combo_order", 0, false);
		studio->set_sensitive("combo_remove", false);
		}
	else
		{
		int draww = draw->allocation.width,
		    drawh = draw->allocation.height;
		studio->set_sensitive("combo_locx", true);
		studio->set_spin("combo_locx", m->tx - combo->starttx,
							0, draww/c_tilesize);
		studio->set_sensitive("combo_locy", true);
		studio->set_spin("combo_locy", m->ty - combo->startty,
							0, drawh/c_tilesize);
		studio->set_sensitive("combo_locz", true);
		studio->set_spin("combo_locz", m->tz, 0, 15);
		studio->set_sensitive("combo_order", true);
		studio->set_spin("combo_order", selected, 0,
						combo->members.size() - 1);
		studio->set_sensitive("combo_remove", true);
		}
	setting_controls = false;
	}
