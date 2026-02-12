lt_dlhandle_iterate (lt_dlinterface_id iface, lt_dlhandle place)
{
  lt_dlhandle handle = place;
  lt__interface_id *iterator = (lt__interface_id *) iface;

  assert (iface);

  if (!handle)
    handle = handles;
  else
    handle = handle->next;


  while (handle && iterator->iface
	 && ((*iterator->iface) (handle, iterator->id_string) != 0))
    {
      handle = handle->next;
    }

  return handle;
}
