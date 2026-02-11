release_grab (GromitData *data,
		   GdkDevice *dev)
{
  if(!dev)
    {
      GHashTableIter it;
      gpointer value;
      GromitDeviceData* devdata;
      g_hash_table_iter_init (&it, data->devdatatable);
      while (g_hash_table_iter_next (&it, NULL, &value))
        {
          devdata = value;
          if(devdata->is_grabbed)
	  {
	    gdk_error_trap_push();
	    gdk_device_ungrab(devdata->device, GDK_CURRENT_TIME);
	    XSync(GDK_DISPLAY_XDISPLAY(data->display), False);
	    if(gdk_error_trap_pop())
	      g_printerr("WARNING: Ungrabbing device '%s' failed.\n", gdk_device_get_name(devdata->device));

	    devdata->is_grabbed = 0;

	    devdata->motion_time = 0;
	  }
        }

      data->all_grabbed = 0;

      if(data->debug)
        g_printerr ("DEBUG: Ungrabbed all Devices.\n");

      return;
    }


  GromitDeviceData *devdata = g_hash_table_lookup(data->devdatatable, dev);

  if (devdata->is_grabbed)
    {
      gdk_device_ungrab(devdata->device, GDK_CURRENT_TIME);
      devdata->is_grabbed = 0;

      devdata->motion_time = 0;


      if(data->debug)
        g_printerr ("DEBUG: Ungrabbed Device '%s'.\n", gdk_device_get_name(devdata->device));
    }

  if (!data->painted)
    hide_window (data);
}
