lt_dlinterface_register (const char *id_string, lt_dlhandle_interface *iface)
{
  lt__interface_id *interface_id = (lt__interface_id *) lt__malloc (sizeof *interface_id);


  if (interface_id)
    {
      interface_id->id_string = lt__strdup (id_string);
      if (!interface_id->id_string)
	FREE (interface_id);
      else
	interface_id->iface = iface;
    }

  return (lt_dlinterface_id) interface_id;
}
