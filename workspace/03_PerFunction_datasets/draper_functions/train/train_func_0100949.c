on_refresh()
{
  const std::vector<JoystickDescription>& joysticks = Joystick::get_joysticks();

  device_list->clear();

  for(std::vector<JoystickDescription>::const_iterator i = joysticks.begin(); i != joysticks.end(); ++i)
    {
      Gtk::ListStore::iterator it = device_list->append();
      (*it)[DeviceListColumns::instance().icon] = Gdk::Pixbuf::create_from_file("/usr/share/jstest-gtk/data/generic.png");
      (*it)[DeviceListColumns::instance().path] = i->filename;

      std::ostringstream out;
      out << i->name << "\n"
          << "Device: " << i->filename << "\n"
          << "Axes: " << i->axis_count << "\n"
          << "Buttons: " << i->button_count;
      (*it)[DeviceListColumns::instance().name] = out.str();
    }

  if (!joysticks.empty())
    treeview.get_selection()->select(device_list->children().begin());
}
